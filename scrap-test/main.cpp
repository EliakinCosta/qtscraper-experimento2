#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>

#include <QXmlQuery>
#include <tidy.h>
#include <tidybuffio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("/home/sandroandrade/tmp/teste.html");
    file.open(QIODevice::ReadOnly);
    QString payload = file.readAll();

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

    payload = QString::fromUtf8(reinterpret_cast<char*>(output.bp));

    QXmlQuery xmlQuery;
    QStringList list;
    xmlQuery.setFocus(payload);

    xmlQuery.setQuery("//table[@class='borda']/thead/tr[1]/th/concat(string(),'^',(@rowspan | @colspan)/local-name(),'^',(@rowspan | @colspan))");
    xmlQuery.evaluateTo(&list);

    QStringList list2;
    xmlQuery.setFocus(payload);
    xmlQuery.setQuery("//table[@class='borda']/thead/tr[2]/th/concat(string(),'^',(@rowspan | @colspan)/local-name(),'^',(@rowspan | @colspan))");
    xmlQuery.evaluateTo(&list2);

    QStringList finalHeaders;
    int list2Position = 0;
    for (auto &string : list) {
        if (string.split('^')[1] == QStringLiteral("colspan")) {
            for (int i = 0; i < string.split('^')[2].toInt(); ++i)
                finalHeaders << string.split('^')[0] + "-" + list2[list2Position++].split('^')[0];
        } else {
            finalHeaders << string.split('^')[0];
        }
    }
    qDebug() << finalHeaders.size() << finalHeaders;
    finalHeaders.removeAll("Ações");

    QStringList list3;
    xmlQuery.setFocus(payload);
    xmlQuery.setQuery("//table[@class='borda']/tbody/tr/string()");
    xmlQuery.evaluateTo(&list3);
    for (auto &fields : list3) {
        fields.remove(QRegularExpression(QStringLiteral("^\n|\n$")));
        int i = 0;
        for (auto &header : finalHeaders) {
            qDebug() << header << ": " << fields.split(QStringLiteral("\n"))[i++];
        }
    }

    xmlQuery.setQuery("//*[@id='ano_periodo']/option/string()");
    list.clear();
    xmlQuery.evaluateTo(&list);
    qDebug() << list;
}
