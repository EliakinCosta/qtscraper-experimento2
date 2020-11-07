#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QElapsedTimer>

class ScrapReply : public QObject
{
    Q_OBJECT

public:
    explicit ScrapReply(QObject *parent = nullptr);

Q_SIGNALS:
    void finished(const QHash<QString, QStringList> &result);
    void finished(int statusCode, bool result);
};

class NetworkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(SessionState sessionState READ sessionState NOTIFY sessionStateChanged)
    Q_PROPERTY(UserType userType READ userType NOTIFY userTypeChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
    Q_PROPERTY(QJsonObject myData READ myData NOTIFY myDataChanged)
    Q_PROPERTY(QStringList terms READ terms NOTIFY termsChanged)
    Q_PROPERTY(QJsonArray courses READ courses NOTIFY coursesChanged)
    Q_PROPERTY(QJsonArray courseParts READ courseParts NOTIFY coursePartsChanged)
    Q_PROPERTY(QJsonArray courseClasses READ courseClasses NOTIFY courseClassesChanged)
    Q_PROPERTY(QJsonArray courseStudents READ courseStudents NOTIFY courseStudentsChanged)
    Q_PROPERTY(QJsonArray IFBANews READ IFBANews NOTIFY IFBANewsChanged)
    Q_PROPERTY(QJsonArray PRPGINotices READ PRPGINotices NOTIFY PRPGINoticesChanged)
    Q_PROPERTY(QString news READ news NOTIFY newsChanged)
    Q_PROPERTY(QStringList gradesReportTerms READ gradesReportTerms NOTIFY gradesReportTermsChanged)
    Q_PROPERTY(QJsonArray gradesReport READ gradesReport NOTIFY gradesReportChanged)
    Q_PROPERTY(QJsonArray gradesReportDetails READ gradesReportDetails NOTIFY gradesReportDetailsChanged)
    Q_PROPERTY(QString seiPublicSearchCaptcha READ seiPublicSearchCaptcha NOTIFY seiPublicSearchCaptchaChanged)
    Q_PROPERTY(QJsonObject seiProcessDetails READ seiProcessDetails NOTIFY seiProcessDetailsChanged)

public:
    explicit NetworkController(QObject *parent = nullptr);
    virtual ~NetworkController() = default;

    enum Status { Null = 0, Loading, Ready, Error };
    Q_ENUM(Status)
    NetworkController::Status status() const;

    enum SessionState { LoggedOut = 0, LoggedIn };
    Q_ENUM(SessionState)
    SessionState sessionState() const;

    enum class Method { Get = 0, Post };

    enum class UserType { Professor = 0, Student = 1 };
    Q_ENUM(UserType)
    NetworkController::UserType userType() const;

    enum class EvaluationMode { AsArray = 0, AsString };

    void setCookies(const QString &cookies);
    QString errorString() const;
    QString username() const;
    QJsonObject myData() const;
    QStringList terms() const;
    QJsonArray courses() const;
    QJsonArray courseParts() const;
    QJsonArray courseClasses() const;
    QJsonArray courseStudents() const;
    QJsonArray IFBANews() const;
    QJsonArray PRPGINotices() const;
    QString news() const;
    QStringList gradesReportTerms() const;
    QJsonArray gradesReport() const;
    QJsonArray gradesReportDetails() const;
    QString seiPublicSearchCaptcha() const;
    QJsonObject seiProcessDetails() const;

    void checkVersion();
    Q_INVOKABLE void getBasicData();
    Q_INVOKABLE void getMyData();
    Q_INVOKABLE void getCourses(const QString &term);
    Q_INVOKABLE void getCourseClasses(const QString &courseId, const QString &coursePartId = QStringLiteral("1"));
    Q_INVOKABLE void getCourseStudents(const QString &courseId, int totalClasses, const QString &coursePartId);
    Q_INVOKABLE void registerUpdateClass(const QString &courseId, const QString &coursePartId, const QString &hours, const QString &date, const QString &description, const QString &previousPartId, const QString &classId = QStringLiteral(""));
    Q_INVOKABLE void registerUpdateAttendance(const QString &classId, const QVariantMap &attendances, const QString &courseId, const QString &partId);
    Q_INVOKABLE void removeClass(const QString &classId, int index, const QString &courseId, const QString &previousPartId);

    Q_INVOKABLE void getIFBANews();
    Q_INVOKABLE void getIFBANews(const QString &newsUrl);
    Q_INVOKABLE void getPRPGINotices();

    Q_INVOKABLE void getStudentDocument(QString documentName, const QString &url);
    Q_INVOKABLE void getGradesReport(const QString &term = QStringLiteral(""));
    Q_INVOKABLE void getGradesReportDetails(const QString &url);

    Q_INVOKABLE void resetSEIPublicSearchAttempts();
    Q_INVOKABLE void prepareSEIPublicSearch(bool emitPrepared = true);
    Q_INVOKABLE void searchSEIProcess(const QString &processNumber, const QString &captcha);
    Q_INVOKABLE void getSEIProcessDetails(const QString &url);
public slots:
    void benchmarkGrades(const QJsonArray &gradesReport);
    void benchmarkAllNews(const QJsonArray &IFBANews);
    void benchmarkdetailsNews(const QString &news);
Q_SIGNALS:
    void newVersionAvailable();
    void userAuthenticated();
    void statusChanged(NetworkController::Status);
    void sessionStateChanged(NetworkController::SessionState);
    void userTypeChanged(NetworkController::UserType);
    void errorStringChanged(const QString &errorString);
    void usernameChanged(const QString &username);
    void myDataChanged(const QJsonObject &myData);
    void termsChanged(const QStringList &terms);
    void coursesChanged(const QJsonArray &courses);
    void coursePartsChanged(const QJsonArray &courseParts);
    void courseClassesChanged(const QJsonArray &courseClasses);
    void courseStudentsChanged(const QJsonArray &courseStudents);
    void IFBANewsChanged(const QJsonArray &IFBANews);
    void PRPGINoticesChanged(const QJsonArray &PRPGINotices);
    void newsChanged(const QString &news);
    void gradesReportTermsChanged(const QStringList &gradesReportTerms);
    void gradesReportChanged(const QJsonArray &gradesReport);
    void gradesReportDetailsChanged(const QJsonArray &gradesReportDetails);
    void seiPublicSearchCaptchaChanged(const QString &seiPublicCaptcha);
    void seiProcessDetailsChanged(const QJsonObject &seiProcessDetails);
    void seiPublicSearchPrepared();
    void seiProcessDetailsAvailable();

private:
    void setStatus(Status status);
    void setSessionState(SessionState sessionState);
    void setErrorString(const QString &errorString);
    void setUsername(const QString &username);
    void setMyData(const QJsonObject &myData);
    void setTerms(const QStringList &terms);
    void setCourses(const QJsonArray &courses);
    void setCourseParts(const QJsonArray &courseParts);
    void setCourseClasses(const QJsonArray &courseClasses);
    void setCourseStudents(const QJsonArray &courseStudents);
    void setIFBANews(const QJsonArray &IFBANews);
    void setPRPGINotices(const QJsonArray &PRPGINotices);
    void setNews(const QString &news);
    void setGradesReportTerms(const QStringList &gradesReportTerms);
    void setGradesReport(const QJsonArray &gradesReport);
    void setGradesReportDetails(const QJsonArray &gradesReportDetails);
    void setSeiPublicSearchCaptcha(const QString &seiPublicSearchCaptcha);
    void setSeiProcessDetails(const QJsonObject &seiProcessDetails);
    static void tidyPayload(QString &payload);
    ScrapReply *scrap(const QString &endpoint, const QHash<QString, QString> &queries, Method method = NetworkController::Method::Get, const QVariantMap &data = QVariantMap());
    ScrapReply *verify(const QString &endpoint, const QString &regExp = QString(), Method method = NetworkController::Method::Get, const QVariantMap &data = QVariantMap());
    QNetworkReply *createNetworkReply(const QString &endpoint, Method method = NetworkController::Method::Get, const QVariantMap &data = QVariantMap());

    static constexpr char _SERVERURL[] = "https://suap.ifba.edu.br/";
    QHash<QString, QString> _dayHash = {
        { QStringLiteral("2"), QStringLiteral("Segunda-feira") },
        { QStringLiteral("3"), QStringLiteral("Terça-feira") },
        { QStringLiteral("4"), QStringLiteral("Quarta-feira") },
        { QStringLiteral("5"), QStringLiteral("Quinta-feira") },
        { QStringLiteral("6"), QStringLiteral("Sexta-feira") }
    };
    QHash<QString, QString> _timeHash = {
        { QStringLiteral("4"), QStringLiteral("17:00") },
        { QStringLiteral("5"), QStringLiteral("17:50") },
        { QStringLiteral("6"), QStringLiteral("18:40") },
        { QStringLiteral("7"), QStringLiteral("19:30") },
        { QStringLiteral("8"), QStringLiteral("20:20") },
        { QStringLiteral("9"), QStringLiteral("21:10") },
        { QStringLiteral("10"), QStringLiteral("22:00") },
    };
    QHash<QString, QString> _gradesHash = {
        { QStringLiteral("Diário"), QStringLiteral("courseId") },
        { QStringLiteral("Disciplina"), QStringLiteral("courseName") },
        { QStringLiteral("C. H."), QStringLiteral("workload") },
        { QStringLiteral("T. de Aulas"), QStringLiteral("totalClasses") },
        { QStringLiteral("T. Faltas"), QStringLiteral("totalUnattendances") },
        { QStringLiteral("% Freq."), QStringLiteral("attendance") },
        { QStringLiteral("Situação"), QStringLiteral("situation") },
        { QStringLiteral("N1-N"), QStringLiteral("part1Grade") },
        { QStringLiteral("N1-F"), QStringLiteral("part1Unattendances") },
        { QStringLiteral("N2-N"), QStringLiteral("part2Grade") },
        { QStringLiteral("N2-F"), QStringLiteral("part2Unattendances") },
        { QStringLiteral("N3-N"), QStringLiteral("part3Grade") },
        { QStringLiteral("N3-F"), QStringLiteral("part3Unattendances") },
        { QStringLiteral("N4-N"), QStringLiteral("part4Grade") },
        { QStringLiteral("N4-F"), QStringLiteral("part4Unattendances") },
        { QStringLiteral("MD"), QStringLiteral("partsGrade") },
        { QStringLiteral("NAF-N"), QStringLiteral("finalPartGrade") },
        { QStringLiteral("NAF-F"), QStringLiteral("finalPartUnattendances") },
        { QStringLiteral("MFD/\nConceito"), QStringLiteral("finalGrade") },
    };
    QNetworkAccessManager _networkAccessManager;
    int _pendingRequests;
    QNetworkRequest _request;
    QString _payload;
    Status _status;
    SessionState _sessionState;
    QString _errorString;
    QString _login;
    QString _username;
    QJsonObject _myData;
    QStringList _terms;
    QJsonArray _courses;
    QJsonArray _courseParts;
    QJsonArray _courseClasses;
    QJsonArray _courseStudents;
    QJsonArray _IFBANews;
    QJsonArray _PRPGINotices;
    QString _news;
    QStringList _gradesReportTerms;
    QJsonArray _gradesReport;
    QJsonArray _gradesReportDetails;
    QString _csrfMiddlewareToken;
    UserType _userType;
    int _statusCode;
    QString _redirectLocation;
    QString _studentId;
    QString _professorId;
    QString _seiPublicSearchCaptcha;
    QString _seiHdnCaptchaMd5;
    int _searchSEIProcessAttempts;
    QJsonObject _seiProcessDetails;
    QElapsedTimer m_timer;
};

#endif // NETWORKCONTROLLER_H
