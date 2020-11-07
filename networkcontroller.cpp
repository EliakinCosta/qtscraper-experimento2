#include "networkcontroller.h"

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniObject>
#endif
#include <QJsonObject>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QSettings>
#include <QUrlQuery>
#include <QXmlQuery>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QDir>
#include <QTextCodec>
#include <QElapsedTimer>
#include <qqml.h>

#include <QJsonArray>
#include <tidy.h>
#include <tidybuffio.h>

#include "core.h"

ScrapReply::ScrapReply(QObject *parent)
    : QObject {parent}
{
}

NetworkController::NetworkController(QObject *parent)
    : QObject {parent},
      _pendingRequests(0),
      _status {NetworkController::Null},
      _sessionState {NetworkController::LoggedOut},
      _userType {UserType::Student}
{
    qmlRegisterInterface<NetworkController>("NetworkController");
    qmlRegisterUncreatableMetaObject(NetworkController::staticMetaObject,
                                     "br.ifba.edu.emile", 1, 0,
                                     "NetworkController",
                                     QStringLiteral("Access to enums only"));

    _request.setHeader(QNetworkRequest::ContentTypeHeader,
                       QStringLiteral("application/x-www-form-urlencoded"));
    QSslConfiguration conf = _request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    _request.setSslConfiguration(conf);

    QSettings settings("ifba", "emile-cookies");
    QString cookies = settings.value("cookies").toString();
    if (!cookies.isEmpty())
        setCookies(cookies);

#ifdef Q_OS_ANDROID
    checkVersion();
#endif
}

NetworkController::Status NetworkController::status() const
{
    return _status;
}

NetworkController::SessionState NetworkController::sessionState() const
{
    return _sessionState;
}

NetworkController::UserType NetworkController::userType() const
{
    return _userType;
}

void NetworkController::setCookies(const QString &cookies)
{
    auto cookieJar = _networkAccessManager.cookieJar();
    for (const auto &cookie : cookieJar->cookiesForUrl(QUrl("https://suap.ifba.edu.br/"))) {
        if (cookie.name() == "csrftoken" || cookie.name() == "sessionid")
            cookieJar->deleteCookie(cookie);
    }
    for (const auto &newCookie : cookies.split(';')) {
        auto newCookieValues = newCookie.split('=');
        QNetworkCookie newCookieObject(newCookieValues.first().trimmed().toLatin1(), newCookieValues.last().trimmed().toLatin1());
        newCookieObject.setDomain("suap.ifba.edu.br");
        newCookieObject.setPath("/");
        cookieJar->insertCookie(newCookieObject);
    }
}

QString NetworkController::errorString() const
{
    return _errorString;
}

QString NetworkController::username() const
{
    return _username;
}

QJsonObject NetworkController::myData() const
{
    return _myData;
}

QStringList NetworkController::terms() const
{
    return _terms;
}

QJsonArray NetworkController::courses() const
{
    return _courses;
}

QJsonArray NetworkController::courseParts() const
{
    return _courseParts;
}

QJsonArray NetworkController::courseClasses() const
{
    return _courseClasses;
}

QJsonArray NetworkController::courseStudents() const
{
    return _courseStudents;
}

QJsonArray NetworkController::IFBANews() const
{
    return _IFBANews;
}

QJsonArray NetworkController::PRPGINotices() const
{
    return _PRPGINotices;
}

QString NetworkController::news() const
{
    return _news;
}

QStringList NetworkController::gradesReportTerms() const
{
    return _gradesReportTerms;
}

QJsonArray NetworkController::gradesReport() const
{
    return _gradesReport;
}

QJsonArray NetworkController::gradesReportDetails() const
{
    return _gradesReportDetails;
}

QString NetworkController::seiPublicSearchCaptcha() const
{
    return _seiPublicSearchCaptcha;
}

QJsonObject NetworkController::seiProcessDetails() const
{
    return _seiProcessDetails;
}

void NetworkController::checkVersion()
{
    auto scrapReply = scrap(QStringLiteral("https://play.google.com/store/apps/details?id=br.edu.ifba.gsort.emile&hl=en"),
    { { QStringLiteral("currentVersion"), QStringLiteral("S^//*[@id='fcxH9b']/div[4]/c-wiz/div/div[2]/div/div[1]/div/c-wiz[4]/div[1]/div[2]/div/div[4]/div[2]/string()") } });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list) {
        scrapReply->deleteLater();
        if (!list["currentVersion"].isEmpty()) {
        QString currentVersion = list["currentVersion"].first().remove(QStringLiteral("\n"));
            if (!currentVersion.isEmpty() && currentVersion != QStringLiteral(VERSION)) {
                Q_EMIT newVersionAvailable();
            }
        }
    });
}

void NetworkController::getBasicData()
{
    QString endpoint = (_userType == UserType::Student) ? QStringLiteral("/edu/salas_virtuais/"):QStringLiteral("/");
    auto scrapReply = scrap(endpoint,
    {
        { QStringLiteral("terms"), QStringLiteral("//*[@id='select_ano_periodo']/option/string()") },
        { QStringLiteral("username"), QStringLiteral("//*[@id='user-tools']/span/string()") },
        { QStringLiteral("login"), QStringLiteral("//*[@id='user-tools']/a/@href/string()") },
        { QStringLiteral("professorId"), QStringLiteral("//div[@class='flex-container']/div[2]/div/ul/li[1]/a/@href/string()") }
    });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
#ifdef Q_OS_ANDROID
        if (_statusCode == 302 && _redirectLocation.startsWith(QStringLiteral("/accounts/login/"))) {
            _userType = UserType::Student;
            QAndroidJniObject viewController ("br/edu/ifba/gsort/emile/WebViewController",
                                        "(Landroid/app/Activity;J)V",
                                        QtAndroid::androidActivity().object(),
                                        reinterpret_cast<quintptr>(this));
            return;
        }
#endif
        if (_statusCode == 404) {
            _userType = UserType::Professor;
            getBasicData();
            return;
        }

        setTerms(list["terms"]);
        if (list["username"].isEmpty()) {
            setErrorString(QStringLiteral("erro ao obter username!"));
            setStatus(NetworkController::Error);
            return;
        }
        setUsername(list["username"].first());
        if (!list["professorId"].isEmpty() && list["professorId"].first().split('/').size() >= 4 && _userType == UserType::Professor) {
            _professorId = list["professorId"].first().split('/')[3];
        }
        setSessionState(NetworkController::LoggedIn);
        if (list["login"].isEmpty() || list["login"].first().split('/').size() < 4) {
            setErrorString(QStringLiteral("erro ao obter login!"));
            setStatus(NetworkController::Error);
            return;
        }
        _login = list["login"].first().split('/')[3];

        Q_EMIT userAuthenticated();
    });
}

void NetworkController::getMyData()
{
    QString endpoint;
    ScrapReply *scrapReply = nullptr;
    if (_userType == UserType::Student) {
        endpoint = QStringLiteral("/edu/aluno/%1/?tab=dados_academicos").arg(_login);
        scrapReply = scrap(endpoint,
        {
            { QStringLiteral("generalInformation"), QStringLiteral("//*[@id='content']/div[2]/div/div[2]/table/tr/td/string()") },
            { QStringLiteral("academicInformation"), QStringLiteral("//div[@data-tab='dados_academicos']/div[2]/div/table/tr/td/string()") },
            { QStringLiteral("courseInformation"), QStringLiteral("//div[@data-tab='dados_academicos']/div[3]/div/table/tr/td/string()") },
            { QStringLiteral("quotaInformation"), QStringLiteral("//div[@data-tab='dados_academicos']/div[4]/div/table/tr/td/string()") }
        });
    } else {
        endpoint = QStringLiteral("/edu/professor/%1/?tab=dados_funcionais").arg(_professorId);
        scrapReply = scrap(endpoint,
        {
            { QStringLiteral("generalInformationHeaders"), QStringLiteral("//*[@id='content']/div[2]/div/table/tr/td[1]/string()") },
            { QStringLiteral("generalInformationValues"), QStringLiteral("//*[@id='content']/div[2]/div/table/tr/td[2]/string()") },
            { QStringLiteral("professorInformationHeaders"), QStringLiteral("//div[@data-tab='dados_funcionais']/div/div/table/tr/td[1]/string()") },
            { QStringLiteral("professorInformationValues"), QStringLiteral("//div[@data-tab='dados_funcionais']/div/div/table/tr/td[2]/string()") }
        });
    }
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        QJsonObject myData;
        if (_userType == UserType::Student) {
            QJsonArray generalInformation;
            for (auto i = list["generalInformation"].begin(); i != list["generalInformation"].end(); i+=2)
                if (!(*(i+1)).trimmed().remove('-').isEmpty()) {
                    generalInformation.append(QJsonObject {
                        { QStringLiteral("header"), i->remove(QRegularExpression(QStringLiteral(":$"))) },
                        { QStringLiteral("value"), (i+1)->remove(QRegularExpression(QStringLiteral("^\n|\n$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) }
                    });
                }
            myData["generalInformation"] = generalInformation;

            QJsonArray academicInformation;
            for (auto i = list["academicInformation"].begin(); i != list["academicInformation"].end(); i+=2)
                if (!(*(i+1)).trimmed().remove('-').isEmpty()) {
                    academicInformation.append(QJsonObject {
                        { QStringLiteral("header"), i->remove(QRegularExpression(QStringLiteral(":$"))) },
                        { QStringLiteral("value"), (i+1)->remove(QRegularExpression(QStringLiteral("^\n|\n$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) }
                    });
                }
            myData["academicInformation"] = academicInformation;

            QJsonArray courseInformation;
            for (auto i = list["courseInformation"].begin(); i != list["courseInformation"].end(); i+=2)
                if (!(*(i+1)).trimmed().remove('-').isEmpty()) {
                    courseInformation.append(QJsonObject {
                        { QStringLiteral("header"), i->remove(QRegularExpression(QStringLiteral(":$"))) },
                        { QStringLiteral("value"), (i+1)->remove(QRegularExpression(QStringLiteral("^\n|\n$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) }
                    });
                }
            myData["courseInformation"] = courseInformation;

            QJsonArray quotaInformation;
            for (auto i = list["quotaInformation"].begin(); i != list["quotaInformation"].end(); i+=2)
                if (!(*(i+1)).trimmed().remove('-').isEmpty()) {
                    quotaInformation.append(QJsonObject {
                        { QStringLiteral("header"), i->remove(QRegularExpression(QStringLiteral(":$"))) },
                        { QStringLiteral("value"), (i+1)->remove(QRegularExpression(QStringLiteral("^\n|\n$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) }
                    });
                }
            myData["quotaInformation"] = quotaInformation;
        } else {
            QJsonArray generalInformation;
            for (auto &generalInformationHeader : list["generalInformationHeaders"])
                if (!list["generalInformationValues"][generalInformation.size()].trimmed().remove('-').remove(QStringLiteral("None")).isEmpty()) {
                    generalInformation.append(QJsonObject {
                        { QStringLiteral("header"), generalInformationHeader.remove(QRegularExpression(QStringLiteral(":$"))) },
                        { QStringLiteral("value"), list["generalInformationValues"][generalInformation.size()].remove(QRegularExpression(QStringLiteral("^\n|\n$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) }
                    });
                }
            myData["generalInformation"] = generalInformation;

            QJsonArray professorInformation;
            for (auto &professorInformationHeader : list["professorInformationHeaders"])
                if (!list["professorInformationValues"][professorInformation.size()].trimmed().remove('-').remove(QStringLiteral("None")).isEmpty()) {
                    professorInformation.append(QJsonObject {
                        { QStringLiteral("header"), professorInformationHeader.remove(QRegularExpression(QStringLiteral(":$"))) },
                        { QStringLiteral("value"), list["professorInformationValues"][professorInformation.size()].remove(QRegularExpression(QStringLiteral("^\n|\n$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) }
                    });
                }
            myData["professorInformation"] = professorInformation;
        }
        setMyData(myData);
    });
}

void NetworkController::getCourses(const QString &term)
{
    ScrapReply *scrapReply = nullptr;
    if (_userType == UserType::Professor) {
        scrapReply = scrap(QStringLiteral("/edu/locais_aula_professor/?&ano-periodo=%1").arg(term),
        {
            { QStringLiteral("courses"), QStringLiteral("//*[@id='content']/div[3]/div/table/tbody/tr/td[1]/string()") },
            { QStringLiteral("timetables"), QStringLiteral("//*[@id='content']/div[3]/div/table/tbody/tr/td[4]/string()") },
        });
    } else {
        scrapReply = scrap(QStringLiteral("/edu/aluno/%1/?tab=locais_aula_aluno&ano-periodo=%2").arg(_login).arg(term),
        {
            { QStringLiteral("coursesIds"), QStringLiteral("//div[@data-tab='locais_aula_aluno']//table//tr/td[1]/string()") },
            { QStringLiteral("courses"), QStringLiteral("//div[@data-tab='locais_aula_aluno']//table//tr/td[2]/dl/dd[1]/string()") },
            { QStringLiteral("timetables"), QStringLiteral("//div[@data-tab='locais_aula_aluno']//table//tr/td[4]/string()") },
            { QStringLiteral("professorNames"), QStringLiteral("//div[@data-tab='locais_aula_aluno']//table//tr/td[2]/dl/dd[2]/string()") },
            { QStringLiteral("studentId"), QStringLiteral("//*[@id='content']/ul[1]/li[2]/ul/li[1]/a/@href/string()") }
        });
    }
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        QJsonArray coursesArray;
        for (auto &course : list["courses"]) {
            course.remove(QRegularExpression(QStringLiteral("^\n")));
            course.remove(QRegularExpression(QStringLiteral("\n$")));
            course.replace(QStringLiteral("\n"), QStringLiteral(" "));
            QRegularExpression regExp1;
            if (_userType == UserType::Professor) {
                regExp1.setPattern(QStringLiteral("^\\(([0-9]+)\\) - (.*) - (.*) - (.*) \\[(.*)\\]"));
            } else {
                regExp1.setPattern(QStringLiteral("^(.*) - (.*) - (.*) \\[(.*)\\]"));
                if (!list["studentId"].isEmpty() && list["studentId"].first().split('/').size() >= 4)
                    _studentId = list["studentId"].first().split('/')[3];
            }
            auto match1 = regExp1.match(course);
            if (match1.hasMatch()) {
                QRegularExpression regExp2(QStringLiteral("(\\d)[N|V](\\d*)"));
                if (list["timetables"].size() < coursesArray.size()+1) {
                    setErrorString(QStringLiteral("erro ao obter horários das disciplinas!"));
                    setStatus(NetworkController::Error);
                    return;
                }
                auto matchIterator = regExp2.globalMatch(list["timetables"][coursesArray.size()]);
                QJsonArray timetable;
                while (matchIterator.hasNext()) {
                    QRegularExpressionMatch match = matchIterator.next();
                    QString time;
                    if (match.captured(2).length() > 1) {
                        time = QStringLiteral("%1 às %2").arg(_timeHash[match.captured(2).left(1)]).arg(_timeHash[QString::number(match.captured(2).right(1).toInt()+1)]);
                    } else {
                        time = _timeHash[match.captured(2).left(1)];
                    }
                    timetable.append(QJsonObject {
                         { QStringLiteral("day"), _dayHash[match.captured(1)] },
                         { QStringLiteral("time"), time },
                         { QStringLiteral("day_hours"), QString::number(match.captured(2).right(1).toInt()-match.captured(2).left(1).toInt()+1) }
                     });
                }
                QString courseId;
                int delta = 0;
                if (_userType == UserType::Professor) {
                    courseId = match1.captured(1);
                } else {
                    delta = 1;
                    if (list["coursesIds"].size() < coursesArray.size()+1) {
                        setErrorString(QStringLiteral("erro ao obter ids das disciplinas!"));
                        setStatus(NetworkController::Error);
                        return;
                    }
                    courseId = list["coursesIds"][coursesArray.size()];
                }
                QJsonObject jsonObject {
                    { QStringLiteral("id"), courseId },
                    { QStringLiteral("acronym"), match1.captured(2-delta).split(" ").first() },
                    { QStringLiteral("name"), match1.captured(3-delta) },
                    { QStringLiteral("level"), match1.captured(4-delta) },
                    { QStringLiteral("workload"), match1.captured(5-delta) },
                    { QStringLiteral("timetable"), timetable },
                    { QStringLiteral("totalOfUnattendances"), timetable },
                };
                if (_userType == UserType::Student) {
                    if (list["professorNames"].size() < coursesArray.size()+1) {
                        setErrorString(QStringLiteral("erro ao obter nomes dos professores!"));
                        setStatus(NetworkController::Error);
                        return;
                    }
                    jsonObject["professorName"] = list["professorNames"][coursesArray.size()];
                } else {
                    jsonObject["professorName"] = QStringLiteral("");
                }
                coursesArray.append(jsonObject);
            }
        }
        setCourses(coursesArray);
    });
}

void NetworkController::getCourseClasses(const QString &courseId, const QString &coursePartId)
{
    ScrapReply *scrapReply = nullptr;
    if (_userType == UserType::Professor) {
        scrapReply = scrap(QStringLiteral("/edu/meu_diario/%1/%2/").arg(courseId).arg(coursePartId),
        {
            { QStringLiteral("courseClasses"), QStringLiteral("//*[@id='table_registro_aula']/tbody/tr[not(@*)]/string()") },
            { QStringLiteral("courseClassesIds"), QStringLiteral("//*[@id='table_registro_aula']/tbody/tr/td[1]/ul/li[2]/a/@href/string()") },
            { QStringLiteral("courseParts"), QStringLiteral("//div[@class='filter']/select/option/string()") },
            { QStringLiteral("coursePartsClosed"), QStringLiteral("//*[@id='content']/div[2]/div/table[2]/tbody/tr/td[4]/span/string()") },
            { QStringLiteral("coursePartsIds"), QStringLiteral("//div[@class='filter']/select/option/@value/string()") },
            { QStringLiteral("totalClasses"), QStringLiteral("//*[@id='content']/div[2]/div/table[1]/tr[3]/td[2]/string()") },
            { QStringLiteral("classesPercentage"), QStringLiteral("//*[@id='content']/div[2]/div/table[1]/tr[3]/td[4]/div/p/string()") }
        });
    } else {
        scrapReply = scrap(QStringLiteral("/edu/sala_virtual/%1/?tab=aulas").arg(courseId),
        {
            { QStringLiteral("courseClasses"), QStringLiteral("//div[@data-tab='aulas']//table//tr/string()") }
        });
    }
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        if (_userType == UserType::Professor) {
            QJsonArray coursePartsArray;
            for (auto &coursePart : list["courseParts"]) {
                if (list["coursePartsIds"].size() < coursePartsArray.size()+1) {
                    setErrorString(QStringLiteral("erro ao obter ids dos termos!"));
                    setStatus(NetworkController::Error);
                    return;
                }
                if (list["coursePartsClosed"].size() < coursePartsArray.size()+1) {
                    setErrorString(QStringLiteral("erro ao obter status dos termos!"));
                    setStatus(NetworkController::Error);
                    return;
                }
                if (list["totalClasses"].isEmpty()) {
                    setErrorString(QStringLiteral("erro ao obter total de aulas!"));
                    setStatus(NetworkController::Error);
                    return;
                }
                if (list["classesPercentage"].isEmpty()) {
                    setErrorString(QStringLiteral("erro ao obter percentual de aulas!"));
                    setStatus(NetworkController::Error);
                    return;
                }
                coursePartsArray.append(QJsonObject {
                    { QStringLiteral("description"), coursePart },
                    { QStringLiteral("id"), list["coursePartsIds"][coursePartsArray.size()] },
                    { QStringLiteral("closed"), list["coursePartsClosed"][coursePartsArray.size()] },
                    { QStringLiteral("totalClasses"), list["totalClasses"].first().split(' ').first() },
                    { QStringLiteral("totalClassesString"), list["totalClasses"].first() },
                    { QStringLiteral("classesPercentage"), list["classesPercentage"].first().chopped(1) }
                });
            }
            setCourseParts(coursePartsArray);
        }

        QJsonArray courseClassesArray;
        for (auto &courseClass : list["courseClasses"]) {
            courseClass.remove(QRegularExpression(QStringLiteral("^(\n)*")));
            courseClass.remove(QRegularExpression(QStringLiteral("(\n)*$")));
            courseClass.replace(QStringLiteral("\n"), QStringLiteral("\r"));
            QRegularExpression regExp1;
            if (_userType == UserType::Professor) {
                regExp1.setPattern(QStringLiteral("([A-Za-z0-9 ]+)\\r(\\d+)\\r(.*?)\\r(.*?)\\r(.*)$"));
             } else {
                regExp1.setPattern(QStringLiteral("(.*)\\r(\\d+)\\r(\\d+)\\r\\r(\\d+)\\r\\r(.*)\\r(.*)$"));
            }
            auto match1 = regExp1.match(courseClass);
            QRegularExpression regExp2(QStringLiteral("^/comum/excluir/edu/aula/(\\d*?)/$"));
            if (match1.hasMatch()) {
                if (_userType == UserType::Professor) {
                    QString classId;
                    if (!list["courseClassesIds"].isEmpty()) {
                        if (list["courseClassesIds"].size() < courseClassesArray.size()+1) {
                            setErrorString(QStringLiteral("erro ao obter ids das aulas!"));
                            setStatus(NetworkController::Error);
                            return;
                        }
                        auto match2 = regExp2.match(list["courseClassesIds"][courseClassesArray.size()]);
                        classId = match2.captured(1);
                    }
                    courseClassesArray.append(QJsonObject {
                        { QStringLiteral("id"), classId },
                        { QStringLiteral("part"), match1.captured(1) },
                        { QStringLiteral("hours"), match1.captured(2) },
                        { QStringLiteral("date"), match1.captured(3) },
                        { QStringLiteral("professor"), match1.captured(4) },
                        { QStringLiteral("description"), match1.captured(5).replace('\r', ' ') },
                        { QStringLiteral("unattendances"), QStringLiteral("") }
                    });
                } else {
                    courseClassesArray.append(QJsonObject {
                        { QStringLiteral("id"), QStringLiteral("") },
                        { QStringLiteral("part"), QStringLiteral("Unidade %1").arg(match1.captured(2)) },
                        { QStringLiteral("hours"), match1.captured(3) },
                        { QStringLiteral("date"), match1.captured(1) },
                        { QStringLiteral("professor"), match1.captured(6) },
                        { QStringLiteral("description"), match1.captured(5).replace('\r', ' ') },
                        { QStringLiteral("unattendances"), QStringLiteral("%1 falta(s)").arg(match1.captured(4)) }
                    });
                }
            }
        }
        setCourseClasses(courseClassesArray);
        Q_EMIT courseClassesChanged(_courseClasses);
        if (_userType == UserType::Professor) {
            getCourseStudents(courseId, _courseClasses.size(), coursePartId);
        }
    });
}

void NetworkController::getCourseStudents(const QString &courseId, int totalClasses, const QString &coursePartId)
{
    auto scrapReply = scrap(QStringLiteral("/edu/meu_diario/%1/%2/?tab=faltas").arg(courseId).arg(coursePartId),
    {
        { QStringLiteral("studentNames"), QStringLiteral("//*[@id='table_faltas']/tbody/tr[not(@*) and td[2]/div/input]/td[1]/string()") },
        { QStringLiteral("studentNamesClosed"), QStringLiteral("//*[@id='table_faltas']/tbody/tr[not(@*)]/td[1]/string()") },
        { QStringLiteral("studentIds"), QStringLiteral("//*[@id='table_faltas']/tbody/tr[not(@*)]/td[2]/div/input/@name/string()") },
        { QStringLiteral("unattendances"), QStringLiteral("//*[@id='table_faltas']/tbody/tr[not(@*)]/td/div/input/@value/string()") },
        { QStringLiteral("unattendancesClosed"), QStringLiteral("//*[@id='table_faltas']/tbody/tr[not(@*)]/td[@class='align-center']/string()") },
        { QStringLiteral("totalUnattendances"), QStringLiteral("//*[@id='table_faltas']/tbody/tr[not(@*)]/td[%1]/string()").arg(totalClasses+2) },
        { QStringLiteral("token"), QStringLiteral("//*[@id='chamada-form']/form/div[1]/div/input/@value/string()") }
    });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        if (list["token"].isEmpty()) {
            setErrorString(QStringLiteral("erro ao obter token de estudantes!"));
            setStatus(NetworkController::Error);
            return;
        }
        _csrfMiddlewareToken = list["token"].first();
        QJsonArray courseStudentsArray;
        QStringList finalStudentNames = !list["studentNames"].isEmpty() ? list["studentNames"]:list["studentNamesClosed"];
        for (auto &studentName : finalStudentNames) {
            QRegularExpression regExp1(QStringLiteral("\\d*? - (.*?) \\(\\n(.*?)\\) \n"));
            auto match1 = regExp1.match(studentName);
            if (match1.hasMatch()) {
                QRegularExpression regExp2(QStringLiteral("(\\d*);\\d*"));
                QString studentId;
                if (!list["studentIds"].isEmpty()) {
                    if (list["studentIds"].size() < courseStudentsArray.size()+1) {
                        setErrorString(QStringLiteral("erro ao obter ids dos alunos!"));
                        setStatus(NetworkController::Error);
                        return;
                    }
                    auto match2 = regExp2.match(list["studentIds"][courseStudentsArray.size()]);
                    if (match2.hasMatch()) {
                        studentId = match2.captured(1);
                    }
                }
                QRegularExpression regExp3(QStringLiteral("\\nO aluno possui (\\d*) falta\\(s\\) no\\ndiário"), QRegularExpression::InvertedGreedinessOption);
                if (list["totalUnattendances"].size() < courseStudentsArray.size()+1) {
                    setErrorString(QStringLiteral("erro ao obter faltas dos alunos!"));
                    setStatus(NetworkController::Error);
                    return;
                }
                auto match3 = regExp3.match(list["totalUnattendances"][courseStudentsArray.size()]);
                QString totalUnattendances = match3.hasMatch() ? match3.captured(1):"0";
                QJsonObject studentObject {
                    { QStringLiteral("name"), match1.captured(1) },
                    { QStringLiteral("enrollment"), match1.captured(2) },
                    { QStringLiteral("id"), studentId },
                    { QStringLiteral("totalUnattendances"), totalUnattendances }
                };
                QStringList unattendances = !list["unattendances"].isEmpty() ? list["unattendances"]:list["unattendancesClosed"];
                if (!unattendances.isEmpty()) {
                    QJsonArray unattendancesArray;
                    for (int i = 0; i < totalClasses; ++i)
                        unattendancesArray.append(unattendances[courseStudentsArray.size()*totalClasses+i]);
                    studentObject["unattendances"] = unattendancesArray;
                }
                courseStudentsArray.append(studentObject);
            }
        }
        setCourseStudents(courseStudentsArray);
        Q_EMIT courseStudentsChanged(_courseStudents);
    });
}

void NetworkController::registerUpdateClass(const QString &courseId, const QString &coursePartId, const QString &hours, const QString &date, const QString &description, const QString &previousPartId, const QString &classId)
{
    auto scrapReply = scrap(QStringLiteral("/edu/adicionar_aula_diario/%1/%2/?_popup=1").arg(courseId).arg(coursePartId),
    {
        { QStringLiteral("id_professor"), QStringLiteral("//*[@id='id_professor_diario']/option[2]/@value/string()") },
        { QStringLiteral("token"), QStringLiteral("//*[@id='aula_form']/input/@value/string()") }
    });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list) {
        scrapReply->deleteLater();
        if (!list.isEmpty()) {
            if (list["token"].isEmpty()) {
                setErrorString(QStringLiteral("erro ao obter token de atualização de aula!"));
                setStatus(NetworkController::Error);
                return;
            }
            _csrfMiddlewareToken = list["token"].first();
            QString endpoint2 = (classId.isEmpty()) ?
                       QStringLiteral("/edu/adicionar_aula_diario/%1/%2/?_popup=1&popup=1").arg(courseId).arg(coursePartId)
                       :
                       QStringLiteral("/edu/adicionar_aula_diario/%1/%2/%3/?_popup=1&popup=1").arg(courseId).arg(coursePartId).arg(classId);
            if (list["id_professor"].isEmpty()) {
                setErrorString(QStringLiteral("erro ao obter id do professor!"));
                setStatus(NetworkController::Error);
                return;
            }
            auto scrapReply2 = verify(endpoint2,
                                      QStringLiteral(""),
                                      NetworkController::Method::Post,
                                      {
                                          { QStringLiteral("csrfmiddlewaretoken"), _csrfMiddlewareToken },
                                          { QStringLiteral("professor_diario"), list["id_professor"].first() },
                                          { QStringLiteral("quantidade"), hours },
                                          { QStringLiteral("etapa"), coursePartId },
                                          { QStringLiteral("data"), date },
                                          { QStringLiteral("conteudo"), description },
                                          { QStringLiteral("popup"), QStringLiteral("1") }
                                      });
            connect(scrapReply2, QOverload<int, bool>::of(&ScrapReply::finished),
                    this, [=](auto statusCode, auto result) {
                scrapReply2->deleteLater();
                qDebug() << "Status code:" << statusCode;
                qDebug() << "Result:" << result;
                qDebug() << "ErrorString:" << _errorString;
                getCourseClasses(courseId, previousPartId);
            });
        }
    });
}

void NetworkController::registerUpdateAttendance(const QString &classId, const QVariantMap &attendances, const QString &courseId, const QString &partId)
{
    for (QVariantMap::const_iterator iter = attendances.begin(); iter != attendances.end(); ++iter) {
        auto scrapReply = verify(QStringLiteral("/edu/registrar_chamada_ajax/%1/%2/%3/").arg(iter.key()).arg(classId).arg(iter.value().toString()),
                                QStringLiteral("<body>OK</body>"));
        connect(scrapReply, QOverload<int, bool>::of(&ScrapReply::finished),
                this, [=](auto statusCode, auto result) {
            scrapReply->deleteLater();
            if (statusCode != 200 || !result) {
                setErrorString(QStringLiteral("Erro ao registrar chamada"));
            }
        });
    }
    getCourseStudents(courseId, _courseClasses.size(), partId);
}

void NetworkController::removeClass(const QString &classId, int index, const QString &courseId, const QString &previousPartId)
{
    auto scrapReply = scrap(QStringLiteral("/comum/excluir/edu/aula/%1/?_popup=1&_popup=1").arg(classId),
    { { QStringLiteral("token"), QStringLiteral("//*[@id='excluirregistro_form']/input/@value/string()") } });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list) {
        scrapReply->deleteLater();
        if (!list.isEmpty()) {
            if (list["token"].isEmpty()) {
                setErrorString(QStringLiteral("erro ao obter token de remoção de aula!"));
                setStatus(NetworkController::Error);
                return;
            }
            _csrfMiddlewareToken = list["token"].first();
            auto scrapReply = verify(QStringLiteral("/comum/excluir/edu/aula/%1/?_popup=1&_popup=1&popup=1").arg(classId),
                                    QStringLiteral("<script>\\nTINY.box.hide\\(''\\);\\n</script>"),
                                    NetworkController::Method::Post,
                                    {
                                        { QStringLiteral("csrfmiddlewaretoken"), _csrfMiddlewareToken },
                                        { QStringLiteral("confirmar"), QStringLiteral("on") },
                                        { QStringLiteral("popup"), QStringLiteral("1") }
                                    });
            connect(scrapReply, QOverload<int, bool>::of(&ScrapReply::finished),
                    this, [=](auto statusCode, auto result) {
                scrapReply->deleteLater();
                if (statusCode == 200 && result) {
                    _courseClasses.removeAt(index);
                    Q_EMIT courseClassesChanged(_courseClasses);
                    getCourseClasses(courseId, previousPartId);
                }
            });
        }
    });
}

void NetworkController::getIFBANews()
{
    connect(this, &NetworkController::IFBANewsChanged, this, &NetworkController::benchmarkAllNews);
    m_timer.start();
    auto scrapReply = scrap(QStringLiteral("https://portal.ifba.edu.br/noticias-pagina-principal"),
    {
        { QStringLiteral("newsTitles"), QStringLiteral("//*[@id='content-core']/div/h2/a/string()") },
        { QStringLiteral("newsUrls"), QStringLiteral("//*[@id='content-core']/div/h2/a/@href/string()") }
    });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list) {
        scrapReply->deleteLater();
        QJsonArray IFBANewsArray;
        for (auto &newsTitle : list["newsTitles"]) {
            IFBANewsArray.append(QJsonObject {
                { QStringLiteral("title"), newsTitle.remove(QRegularExpression(QStringLiteral("^\n*"))).remove(QRegularExpression(QStringLiteral("\n*$"))).replace(QStringLiteral("\n"), QStringLiteral(" ")) },
                { QStringLiteral("url"), list["newsUrls"][IFBANewsArray.size()] }
            });
        }
        setIFBANews(IFBANewsArray);
    });
}

void NetworkController::getIFBANews(const QString &newsUrl)
{
    connect(this, &NetworkController::newsChanged, this, &NetworkController::benchmarkdetailsNews);
    m_timer.start();
    auto scrapReply = scrap(newsUrl,
    { { QStringLiteral("news"), QStringLiteral("S^//div[@property='rnews:articleBody']") } });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list) {
        scrapReply->deleteLater();
        setNews(list["news"].first().replace(QRegularExpression(QStringLiteral("<a.*?(href=\".*?\").*?>")), QStringLiteral("<a \\1)>")).remove(QRegularExpression(QStringLiteral("<img.*?/>"))).remove(QRegularExpression(QStringLiteral("<dd class=\"image-caption\".*?dd>"), QRegularExpression::DotMatchesEverythingOption)));
    });
}

void NetworkController::getPRPGINotices()
{
    auto scrapReply = scrap(QStringLiteral("https://portal.ifba.edu.br/prpgi/editais/ano-2019/2019"),
    { { QStringLiteral("noticeTitles"), QStringLiteral("//div[@class='tile tile-default']/div/p/string()") } });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list) {
        scrapReply->deleteLater();
        QJsonArray PRPGINoticesArray;
        int i = 3;
        QXmlQuery contentsQuery;
        contentsQuery.setFocus(_payload);
        for (auto &noticeTitle : list["noticeTitles"]) {
            noticeTitle.remove(QRegularExpression(QStringLiteral("^\n")));
            noticeTitle.remove(QRegularExpression(QStringLiteral("\n$")));
            QStringList data = noticeTitle.split(QStringLiteral("\n\n"));
            contentsQuery.setQuery(QString("//*[@id='content']/div[%1]/div/div/div/div").arg(i++));
            QString contents;
            contentsQuery.evaluateTo(&contents);
            PRPGINoticesArray.append(QJsonObject {
                { QStringLiteral("title"), data.first().replace("\n", " ") },
                { QStringLiteral("description"), data.last().replace("\n", " ") },
                { QStringLiteral("contents"), contents.replace(QRegularExpression(QStringLiteral("<a.*?(href=\".*?\").*?>")), QStringLiteral("<a \\1>")) }
            });
        }
        setPRPGINotices(PRPGINoticesArray);
    });
}

void NetworkController::getStudentDocument(QString documentName, const QString &url)
{
    QString newDocumentName = documentName.replace(' ', '-');
    if (_studentId.isEmpty()) {
        auto scrapReply = scrap(QStringLiteral("/edu/aluno/%1/").arg(_login),
        {
            { QStringLiteral("studentId"), QStringLiteral("//*[@id='content']/ul[1]/li[2]/ul/li[1]/a/@href/string()") }
        });
        connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
            scrapReply->deleteLater();
            if (!list["studentId"].isEmpty() && list["studentId"].first().split('/').size() >= 4)
                _studentId = list["studentId"].first().split('/')[3];
            getStudentDocument(documentName, url);
        });
    } else {
        auto reply = createNetworkReply(url + _studentId + "/");
        connect (reply, &QNetworkReply::finished, this, [=]() {
            reply->deleteLater();
            _pendingRequests--;
            if (_pendingRequests == 0)
                setStatus(NetworkController::Ready);

            QFile tmpPdfFile (QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/" + newDocumentName + ".pdf");
#ifdef Q_OS_ANDROID
            QtAndroid::requestPermissionsSync(QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE");
#endif
            tmpPdfFile.open(QIODevice::WriteOnly);
            tmpPdfFile.write(reply->readAll());
            tmpPdfFile.close();
            QFileInfo info1(tmpPdfFile.fileName());
            QDesktopServices::openUrl(QUrl::fromLocalFile(tmpPdfFile.fileName()));
        });
    }
}

void NetworkController::benchmarkGrades(const QJsonArray &gradesReport)
{
    qDebug() << "gradesReport " << m_timer.elapsed() << "ms";
}

void NetworkController::benchmarkAllNews(const QJsonArray &IFBANews)
{
    qDebug() << "allNews " << m_timer.elapsed() << "ms";
}

void NetworkController::benchmarkdetailsNews(const QString &news)
{
    qDebug() << "detailsNews " << m_timer.elapsed() << "ms";
}

void NetworkController::getGradesReport(const QString &term)
{
    connect(this, &NetworkController::gradesReportChanged, this, &NetworkController::benchmarkGrades);
    m_timer.start();
    QString endpoint = QStringLiteral("/edu/aluno/%1/?tab=boletim&ano_periodo=%2").arg(_login).arg(term);
    auto scrapReply = scrap(endpoint,
    {
        { QStringLiteral("terms"), QStringLiteral("//*[@id='ano_periodo']/option/string()") },
        { QStringLiteral("headers1"), QStringLiteral("//table[@class='borda']/thead/tr[1]/th/concat(string(),'^',(@rowspan | @colspan)/local-name(),'^',(@rowspan | @colspan))") },
        { QStringLiteral("headers2"), QStringLiteral("//table[@class='borda']/thead/tr[2]/th/concat(string(),'^',(@rowspan | @colspan)/local-name(),'^',(@rowspan | @colspan))") },
        { QStringLiteral("data"), QStringLiteral("//table[@class='borda']/tbody/tr/string()") },
        { QStringLiteral("detailsLinks"), QStringLiteral("//table[@class='borda']/tbody/tr/td[last()]/a/@href/string()") }
    });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        QStringList finalHeaders;
        int headers2Position = 0;
        for (auto &header : list["headers1"]) {
            if (header.split('^')[1] == QStringLiteral("colspan")) {
                for (int i = 0; i < header.split('^')[2].toInt(); ++i) {
                    finalHeaders << header.split('^')[0] + "-" + list["headers2"][headers2Position++].split('^')[0];
                }
            } else {
                finalHeaders << header.split('^')[0];
            }
        }
        finalHeaders.removeAll("Ações");
        QJsonArray grades;
        int j = 0;
        for (auto &fields : list["data"]) {
            fields.remove(QRegularExpression(QStringLiteral("^\n|\n$")));
            int i = 0;
            QJsonObject grade;
            for (auto &header : finalHeaders) {
                grade[_gradesHash[header]] = fields.split(QStringLiteral("\n"))[i++].remove(QRegularExpression(QStringLiteral("^[A-Z]*\\.[0-9]* - ")));
            }
            if (list["detailsLinks"].size() >= j+1) {
                grade["detailsLink"] = list["detailsLinks"][j];
            }
            grades.append(grade);
            j++;
        }
        for (auto &term : list["terms"]) {
            term.replace('/', '.');
        }
        setGradesReportTerms(list["terms"]);
        setGradesReport(grades);
    });
}

void NetworkController::getGradesReportDetails(const QString &url)
{
    auto scrapReply = scrap(url, {{ QStringLiteral("parts"), QStringLiteral("//*[@id='content']/div[2]/div/h4/string()") }});
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        QJsonArray termGradesArray;
        int i = 1;
        QXmlQuery xmlQuery;
        xmlQuery.setFocus(_payload);
        QStringList gradesList;
        for (auto &part : list["parts"]) {
            xmlQuery.setQuery(QStringLiteral("//*[@id='content']/div[2]/div/table[%1]/tbody/tr/string()").arg(i++));
            gradesList.clear();
            xmlQuery.evaluateTo(&gradesList);
            QJsonObject termObject;
            termObject["gradesTerm"] = part;
            QJsonArray gradesArray;
            for (auto &grade : gradesList) {
                grade.remove(QRegularExpression(QStringLiteral("^\n|\n$")));
                QStringList grades = grade.split(QStringLiteral("\n"));
                gradesArray.append(QJsonObject {
                        {"acronym", grades[0]},
                        {"type", grades[1]},
                        {"description", grades[2]},
                        {"weight", grades[3]},
                        {"grade", grades[4]}
                });
            }
            termObject["grades"] = gradesArray;
            termGradesArray.append(termObject);
        }
        setGradesReportDetails(termGradesArray);
    });
}

void NetworkController::resetSEIPublicSearchAttempts()
{
    _searchSEIProcessAttempts = 0;
}

void NetworkController::prepareSEIPublicSearch(bool emitPrepared)
{
    setSeiPublicSearchCaptcha(QStringLiteral(""));
    auto scrapReply = scrap(QStringLiteral("https://sei.ifba.edu.br/sei/institucional/pesquisa/processo_pesquisar.php?acao_externa=protocolo_pesquisar&acao_origem_externa=protocolo_pesquisar&id_orgao_acesso_externo=0"), {
                                { QStringLiteral("captcha"), QStringLiteral("S^//label[@id='lblCaptcha']/img/@src/string()") },
                                { QStringLiteral("hdnCaptchaMd5"), QStringLiteral("//*[@id='hdnCaptchaMd5']/@value/string()") }
                            });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        if (_statusCode == 500) {
            _searchSEIProcessAttempts++;
            if (_searchSEIProcessAttempts == 5) {
                setErrorString(QStringLiteral("Erro ao acessar página de pesquisa pública do SEI!"));
                setStatus(NetworkController::Error);
            } else {
                prepareSEIPublicSearch(emitPrepared);
            }
        } else {
            setSeiPublicSearchCaptcha(list["captcha"].first().remove(QStringLiteral("\n")));
            _seiHdnCaptchaMd5 = list["hdnCaptchaMd5"].first();
            if (emitPrepared) {
                Q_EMIT seiPublicSearchPrepared();
            }
        }
    });
}

void NetworkController::searchSEIProcess(const QString &processNumber, const QString &captcha)
{
    QString plainProcessNumber = processNumber;
    auto scrapReply = scrap(QStringLiteral("https://sei.ifba.edu.br/sei/institucional/pesquisa/processo_pesquisar.php?acao_externa=protocolo_pesquisar&acao_origem_externa=protocolo_pesquisar&id_orgao_acesso_externo=0"), {
                                { QStringLiteral("processUrl"), QStringLiteral("S^//table[@class='resultado']/tr[1]/td[1]/a[1]/@href/string()") }
                            }, Method::Post, {
                                { QStringLiteral("txtProtocoloPesquisa"), processNumber },
                                { QStringLiteral("txtCaptcha"), captcha },
                                { QStringLiteral("sbmPesquisar"), QStringLiteral("Pesquisar") },
                                { QStringLiteral("chkSinProcessos"), QStringLiteral("P") },
                                { QStringLiteral("hdnCaptchaMd5"), _seiHdnCaptchaMd5 },
                                { QStringLiteral("partialfields"), QStringLiteral("protocolo_formatado_pesquisa%3A*%3B") + plainProcessNumber.remove(QRegularExpression(QStringLiteral("\\.|/|-"))) + QStringLiteral("%3B*+AND+sta_protocolo%3AP") },
                                { QStringLiteral("hdnFlagPesquisa"), QStringLiteral("1") }
                            });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        if (_payload.contains(QStringLiteral("Código de confirmação inválido"))) {
            setErrorString(QStringLiteral("Código de confirmação inválido, tente novamente!"));
            prepareSEIPublicSearch(false);
        } else if (_statusCode == 500) {
            _searchSEIProcessAttempts++;
            if (_searchSEIProcessAttempts == 5) {
                setErrorString(QStringLiteral("Erro ao realizar pesquisa pública do SEI, tente novamente!"));
                setStatus(NetworkController::Error);
            } else {
                searchSEIProcess(processNumber, captcha);
            }
        } else {
            _searchSEIProcessAttempts = 0;
            getSEIProcessDetails(QString("https://sei.ifba.edu.br/sei/institucional/pesquisa/%1").arg(list["processUrl"].first().remove(QRegularExpression(QStringLiteral("\n$")))));
        }
    });
}

void NetworkController::getSEIProcessDetails(const QString &url)
{
    auto scrapReply = scrap(url, {
        { QStringLiteral("data"), QStringLiteral("//table[@id='tblCabecalho']/tr[@class='infraTrClara']/string()") },
        { QStringLiteral("documents"), QStringLiteral("//table[@id='tblDocumentos']/tr[@class='infraTrClara']/string()") },
        { QStringLiteral("moves"), QStringLiteral("//table[@id='tblHistorico']/tr/string()") }
    });
    connect(scrapReply, QOverload<const QHash<QString, QStringList> &>::of(&ScrapReply::finished), this, [=](auto list){
        scrapReply->deleteLater();
        if (_statusCode == 500) {
            _searchSEIProcessAttempts++;
            if (_searchSEIProcessAttempts == 5) {
                setErrorString(QStringLiteral("Erro ao obter dados do processo SEI, tente novamente!"));
                setStatus(NetworkController::Error);
            } else {
                getSEIProcessDetails(url);
            }
        } else {
            if (_payload.contains(QStringLiteral("Sua pesquisa pelo termo não encontrou\nnenhum processo ou documento correspondente"))) {
                setErrorString(QStringLiteral("Processo não encontrado!"));
                return;
            }
            QJsonObject seiProcessDetails;

            QJsonObject seiProcessData;
            for (auto &field : list["data"]) {
                field.remove(QRegularExpression(QStringLiteral("^(\n)*|(\n$)*")));
                QString value = field;
                seiProcessData[field.split("\n").first().chopped(1)] = value.remove(QRegularExpression(QStringLiteral("^.*\n")));
            }
            seiProcessDetails["data"] = seiProcessData;

            QJsonArray seiProcessDocuments;
            for (auto &field : list["documents"]) {
                field.remove(QRegularExpression(QStringLiteral("^(\n)*|(\n$)*")));
                QJsonObject seiProcessDocument;
                QStringList fields = field.split("\n");
                seiProcessDocument["id"] = fields[2];
                seiProcessDocument["type"] = fields[fields.length()-6];
                seiProcessDocument["date"] = fields[fields.length()-4];
                seiProcessDocument["department"] = fields[fields.length()-2];
                seiProcessDocuments.append(seiProcessDocument);
            }
            seiProcessDetails["documents"] = seiProcessDocuments;

            QJsonArray seiProcessMoves;
            list["moves"].takeFirst();
            for (auto &move : list["moves"]) {
                move.remove(QRegularExpression(QStringLiteral("^(\n)*|(\n$)*")));
                move.replace(QStringLiteral("pela unidade \n"), QStringLiteral("pela unidade "));
                QJsonObject seiProcessMove;
                QStringList fields = move.split("\n");
                seiProcessMove["datetime"] = fields[0];
                seiProcessMove["department"] = fields[2];
                seiProcessMove["description"] = fields[4];
                seiProcessMoves.append(seiProcessMove);
            }
            seiProcessDetails["moves"] = seiProcessMoves;
            setSeiProcessDetails(seiProcessDetails);
            Q_EMIT seiProcessDetailsAvailable();
        }
    });
}

void NetworkController::setStatus(NetworkController::Status status)
{
    if (_status != status) {
        _status = status;
        Q_EMIT statusChanged(_status);
    }
}

void NetworkController::setSessionState(NetworkController::SessionState sessionState)
{
    if (_sessionState != sessionState) {
        _sessionState = sessionState;
        Q_EMIT sessionStateChanged(_sessionState);
    }
}

void NetworkController::setErrorString(const QString &errorString)
{
    _errorString = errorString;
    Q_EMIT errorStringChanged(_errorString);
}

void NetworkController::setUsername(const QString &username)
{
    if (_username != username) {
        _username = username;
        Q_EMIT usernameChanged(_username);
    }
}

void NetworkController::setMyData(const QJsonObject &myData)
{
    if (_myData != myData) {
        _myData = myData;
        Q_EMIT myDataChanged(_myData);
    }
}

void NetworkController::setTerms(const QStringList &terms)
{
    if (_terms != terms) {
        _terms = terms;
        Q_EMIT termsChanged(_terms);
    }
}

void NetworkController::setCourses(const QJsonArray &courses)
{
    if (_courses != courses) {
        _courses = courses;
        Q_EMIT coursesChanged(_courses);
    }
}

void NetworkController::setCourseParts(const QJsonArray &courseParts)
{
    if (_courseParts != courseParts) {
        _courseParts = courseParts;
        Q_EMIT coursePartsChanged(_courseParts);
    }
}

void NetworkController::setCourseClasses(const QJsonArray &courseClasses)
{
    if (_courseClasses != courseClasses) {
        _courseClasses = courseClasses;
        Q_EMIT courseClassesChanged(_courseClasses);
    }
}

void NetworkController::setCourseStudents(const QJsonArray &courseStudents)
{
    if (_courseStudents != courseStudents) {
        _courseStudents = courseStudents;
        Q_EMIT courseStudentsChanged(_courseStudents);
    }
}

void NetworkController::setIFBANews(const QJsonArray &IFBANews)
{
    if (_IFBANews != IFBANews) {
        _IFBANews = IFBANews;        
    }
    Q_EMIT IFBANewsChanged(_IFBANews);
}

void NetworkController::setPRPGINotices(const QJsonArray &PRPGINotices)
{
    if (_PRPGINotices != PRPGINotices) {
        _PRPGINotices = PRPGINotices;
        Q_EMIT PRPGINoticesChanged(_PRPGINotices);
    }
}

void NetworkController::setNews(const QString &news)
{
    if (_news != news) {
        _news = news;
        Q_EMIT newsChanged(_news);
    }
}

void NetworkController::setGradesReportTerms(const QStringList &gradesReportTerms)
{
    if (_gradesReportTerms != gradesReportTerms) {
        _gradesReportTerms = gradesReportTerms;
        Q_EMIT gradesReportTermsChanged(_gradesReportTerms);
    }
}

void NetworkController::setGradesReport(const QJsonArray &gradesReport)
{
    if (_gradesReport != gradesReport) {
        _gradesReport = gradesReport;
        Q_EMIT gradesReportChanged(_gradesReport);
    }
}

void NetworkController::setGradesReportDetails(const QJsonArray &gradesReportDetails)
{
    if (_gradesReportDetails != gradesReportDetails) {
        _gradesReportDetails = gradesReportDetails;
        Q_EMIT gradesReportDetailsChanged(_gradesReportDetails);
    }
}

void NetworkController::setSeiPublicSearchCaptcha(const QString &seiPublicSearchCaptcha)
{
    if (_seiPublicSearchCaptcha != seiPublicSearchCaptcha) {
        _seiPublicSearchCaptcha = seiPublicSearchCaptcha;
        Q_EMIT seiPublicSearchCaptchaChanged(_seiPublicSearchCaptcha);
    }
}

void NetworkController::setSeiProcessDetails(const QJsonObject &seiProcessDetails)
{
    if (_seiProcessDetails != seiProcessDetails) {
        _seiProcessDetails = seiProcessDetails;
        Q_EMIT seiProcessDetailsChanged(_seiProcessDetails);
    }
}

void NetworkController::tidyPayload(QString &payload)
{
    TidyDoc tdoc = tidyCreate();
    tidyOptSetBool(tdoc, TidyXmlOut, yes);
    tidyOptSetBool(tdoc, TidyQuiet, yes);
    tidyOptSetBool(tdoc, TidyNumEntities, yes);
    tidyOptSetBool(tdoc, TidyUseCustomTags, yes);
    tidyOptSetBool(tdoc, TidyShowWarnings, no);

    tidyParseString(tdoc, payload.toUtf8());
    tidyCleanAndRepair(tdoc);
    TidyBuffer output = {nullptr, nullptr, 0, 0, 0};
    tidySaveBuffer(tdoc, &output);

    payload = QString::fromUtf8(reinterpret_cast<char*>(output.bp)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
}

ScrapReply *NetworkController::scrap(const QString &endpoint, const QHash<QString, QString> &queries, NetworkController::Method method, const QVariantMap &data)
{
    _statusCode = 0;
    _redirectLocation.clear();
    auto reply = createNetworkReply(endpoint, method, data);
    //qDebug() << "Scraping" << endpoint;
    auto scrapReply = new ScrapReply {this};
    connect (reply, &QNetworkReply::finished, this, [=]() {
        _pendingRequests--;
        reply->deleteLater();

        _statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (_statusCode != 404 && reply->error() != QNetworkReply::NetworkError::NoError) {
            // SEI public search returns status code 500 and requires retrial :/
            if (_statusCode != 500 || !endpoint.contains(QStringLiteral("sei.ifba.edu.br"))) {
                setErrorString(QString("%1: %2").arg(_statusCode).arg(reply->errorString().toLower()));
                setStatus(NetworkController::Error);
                Q_EMIT scrapReply->finished(QHash<QString, QStringList>());
                return;
            }
        }
        if (_statusCode == 302) {
            _redirectLocation = reply->rawHeader("Location");
        }
        if (_statusCode != 200 && _statusCode != 302 && _statusCode != 404) {
            // SEI public search returns status code 500 and requires retrial :/
            if (_statusCode != 500 || !endpoint.contains(QStringLiteral("sei.ifba.edu.br"))) {
                setErrorString(QStringLiteral("requisição retornou status code = %1").arg(_statusCode));
                setStatus(NetworkController::Error);
                Q_EMIT scrapReply->finished(QHash<QString, QStringList>());
                return;
            }
        }

        _payload = (endpoint.contains(QStringLiteral("sei.ifba.edu.br"))) ? QTextCodec::codecForName("iso-8859-1")->toUnicode(reply->readAll()):reply->readAll();
        tidyPayload(_payload);
        //qDebug() << _payload;
        QXmlQuery xmlQuery;
        xmlQuery.setFocus(_payload);

        QHash<QString, QStringList> result;
        for (auto i = queries.begin(); i != queries.end(); ++i) {
            EvaluationMode evaluationMode = EvaluationMode::AsArray;
            if (i.value().startsWith(QStringLiteral("S^"))) {
                evaluationMode = EvaluationMode::AsString;
            }
            QString query = i.value();
            xmlQuery.setQuery(query.remove(QRegularExpression(QStringLiteral("^S\\^"))).remove(QRegularExpression(QStringLiteral("^N\\^"))));
            if (!xmlQuery.isValid()) {
                setErrorString(QStringLiteral("sentença xquery inválida"));
                setStatus(NetworkController::Error);
                Q_EMIT scrapReply->finished(QHash<QString, QStringList>());
                return;
            }
            QStringList list;
            QString string;
            if (evaluationMode == EvaluationMode::AsArray) {
                xmlQuery.evaluateTo(&list);
            } else if (evaluationMode == EvaluationMode::AsString) {
                QString string;
                xmlQuery.evaluateTo(&string);
                if (!string.isEmpty())
                    list << string;
            }
            result[i.key()] = list;
        }
        if (_pendingRequests == 0)
            setStatus(NetworkController::Ready);
        Q_EMIT scrapReply->finished(result);
    });

    return scrapReply;
}

ScrapReply *NetworkController::verify(const QString &endpoint, const QString &regExp, NetworkController::Method method, const QVariantMap &data)
{
    _statusCode = 0;
    _redirectLocation.clear();
    auto reply = createNetworkReply(endpoint, method, data);
    auto scrapReply = new ScrapReply {this};
    connect (reply, &QNetworkReply::finished, this, [=]() {
        _pendingRequests--;
        reply->deleteLater();

        _statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (_statusCode != 404 && reply->error() != QNetworkReply::NetworkError::NoError) {
            setErrorString(reply->errorString().toLower());
            qDebug() << "ERRO:" << reply->errorString().toLower();
            setStatus(NetworkController::Error);
            Q_EMIT scrapReply->finished(-1, false);
            return;
        }
        if (_statusCode == 302) {
            _redirectLocation = reply->rawHeader("Location");
        }
        if (_statusCode != 200 && _statusCode != 302 && _statusCode != 404) {
            setErrorString(QStringLiteral("requisição retornou status code = %1").arg(_statusCode));
            setStatus(NetworkController::Error);
            Q_EMIT scrapReply->finished(QHash<QString, QStringList>());
            return;
        }

        _payload = reply->readAll(); // clazy:exclude=qt4-qstring-from-array
        tidyPayload(_payload);
        //qDebug() << payload;
        if (_pendingRequests == 0)
            setStatus(NetworkController::Ready);
        Q_EMIT scrapReply->finished(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                                    QRegularExpression {regExp}.match(_payload).hasMatch());
    });

    return scrapReply;
}

QNetworkReply *NetworkController::createNetworkReply(const QString &endpoint, NetworkController::Method method, const QVariantMap &data)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    if (!endpoint.toLower().startsWith("http")) {
        _request.setUrl(_SERVERURL + endpoint);
    } else {
        _request.setUrl(endpoint);
    }
    _pendingRequests++;
    setStatus(NetworkController::Loading);
    switch(method) {
    case Method::Get:
        return _networkAccessManager.get(_request);
    case Method::Post:
        QString queryString;
        for (QVariantMap::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
          queryString += iter.key() + "=" + iter.value().toString() + "&";
        }
        queryString.chop(1);
        return _networkAccessManager.post(_request, QUrlQuery {queryString}.toString(QUrl::FullyEncoded).toUtf8());
    }
    _pendingRequests--;
    return nullptr;
}
