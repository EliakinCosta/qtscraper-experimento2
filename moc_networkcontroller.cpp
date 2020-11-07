/****************************************************************************
** Meta object code from reading C++ file 'networkcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "networkcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScrapReply_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScrapReply_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScrapReply_t qt_meta_stringdata_ScrapReply = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ScrapReply"
QT_MOC_LITERAL(1, 11, 8), // "finished"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 26), // "QHash<QString,QStringList>"
QT_MOC_LITERAL(4, 48, 6), // "result"
QT_MOC_LITERAL(5, 55, 10) // "statusCode"

    },
    "ScrapReply\0finished\0\0QHash<QString,QStringList>\0"
    "result\0statusCode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScrapReply[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       1,    2,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    5,    4,

       0        // eod
};

void ScrapReply::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScrapReply *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< const QHash<QString,QStringList>(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScrapReply::*)(const QHash<QString,QStringList> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScrapReply::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScrapReply::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScrapReply::finished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScrapReply::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ScrapReply.data,
    qt_meta_data_ScrapReply,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScrapReply::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScrapReply::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScrapReply.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScrapReply::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ScrapReply::finished(const QHash<QString,QStringList> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScrapReply::finished(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_NetworkController_t {
    QByteArrayData data[97];
    char stringdata0[1424];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkController_t qt_meta_stringdata_NetworkController = {
    {
QT_MOC_LITERAL(0, 0, 17), // "NetworkController"
QT_MOC_LITERAL(1, 18, 19), // "newVersionAvailable"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 17), // "userAuthenticated"
QT_MOC_LITERAL(4, 57, 13), // "statusChanged"
QT_MOC_LITERAL(5, 71, 25), // "NetworkController::Status"
QT_MOC_LITERAL(6, 97, 19), // "sessionStateChanged"
QT_MOC_LITERAL(7, 117, 31), // "NetworkController::SessionState"
QT_MOC_LITERAL(8, 149, 15), // "userTypeChanged"
QT_MOC_LITERAL(9, 165, 27), // "NetworkController::UserType"
QT_MOC_LITERAL(10, 193, 18), // "errorStringChanged"
QT_MOC_LITERAL(11, 212, 11), // "errorString"
QT_MOC_LITERAL(12, 224, 15), // "usernameChanged"
QT_MOC_LITERAL(13, 240, 8), // "username"
QT_MOC_LITERAL(14, 249, 13), // "myDataChanged"
QT_MOC_LITERAL(15, 263, 6), // "myData"
QT_MOC_LITERAL(16, 270, 12), // "termsChanged"
QT_MOC_LITERAL(17, 283, 5), // "terms"
QT_MOC_LITERAL(18, 289, 14), // "coursesChanged"
QT_MOC_LITERAL(19, 304, 7), // "courses"
QT_MOC_LITERAL(20, 312, 18), // "coursePartsChanged"
QT_MOC_LITERAL(21, 331, 11), // "courseParts"
QT_MOC_LITERAL(22, 343, 20), // "courseClassesChanged"
QT_MOC_LITERAL(23, 364, 13), // "courseClasses"
QT_MOC_LITERAL(24, 378, 21), // "courseStudentsChanged"
QT_MOC_LITERAL(25, 400, 14), // "courseStudents"
QT_MOC_LITERAL(26, 415, 15), // "IFBANewsChanged"
QT_MOC_LITERAL(27, 431, 8), // "IFBANews"
QT_MOC_LITERAL(28, 440, 19), // "PRPGINoticesChanged"
QT_MOC_LITERAL(29, 460, 12), // "PRPGINotices"
QT_MOC_LITERAL(30, 473, 11), // "newsChanged"
QT_MOC_LITERAL(31, 485, 4), // "news"
QT_MOC_LITERAL(32, 490, 24), // "gradesReportTermsChanged"
QT_MOC_LITERAL(33, 515, 17), // "gradesReportTerms"
QT_MOC_LITERAL(34, 533, 19), // "gradesReportChanged"
QT_MOC_LITERAL(35, 553, 12), // "gradesReport"
QT_MOC_LITERAL(36, 566, 26), // "gradesReportDetailsChanged"
QT_MOC_LITERAL(37, 593, 19), // "gradesReportDetails"
QT_MOC_LITERAL(38, 613, 29), // "seiPublicSearchCaptchaChanged"
QT_MOC_LITERAL(39, 643, 16), // "seiPublicCaptcha"
QT_MOC_LITERAL(40, 660, 24), // "seiProcessDetailsChanged"
QT_MOC_LITERAL(41, 685, 17), // "seiProcessDetails"
QT_MOC_LITERAL(42, 703, 23), // "seiPublicSearchPrepared"
QT_MOC_LITERAL(43, 727, 26), // "seiProcessDetailsAvailable"
QT_MOC_LITERAL(44, 754, 15), // "benchmarkGrades"
QT_MOC_LITERAL(45, 770, 16), // "benchmarkAllNews"
QT_MOC_LITERAL(46, 787, 20), // "benchmarkdetailsNews"
QT_MOC_LITERAL(47, 808, 12), // "getBasicData"
QT_MOC_LITERAL(48, 821, 9), // "getMyData"
QT_MOC_LITERAL(49, 831, 10), // "getCourses"
QT_MOC_LITERAL(50, 842, 4), // "term"
QT_MOC_LITERAL(51, 847, 16), // "getCourseClasses"
QT_MOC_LITERAL(52, 864, 8), // "courseId"
QT_MOC_LITERAL(53, 873, 12), // "coursePartId"
QT_MOC_LITERAL(54, 886, 17), // "getCourseStudents"
QT_MOC_LITERAL(55, 904, 12), // "totalClasses"
QT_MOC_LITERAL(56, 917, 19), // "registerUpdateClass"
QT_MOC_LITERAL(57, 937, 5), // "hours"
QT_MOC_LITERAL(58, 943, 4), // "date"
QT_MOC_LITERAL(59, 948, 11), // "description"
QT_MOC_LITERAL(60, 960, 14), // "previousPartId"
QT_MOC_LITERAL(61, 975, 7), // "classId"
QT_MOC_LITERAL(62, 983, 24), // "registerUpdateAttendance"
QT_MOC_LITERAL(63, 1008, 11), // "attendances"
QT_MOC_LITERAL(64, 1020, 6), // "partId"
QT_MOC_LITERAL(65, 1027, 11), // "removeClass"
QT_MOC_LITERAL(66, 1039, 5), // "index"
QT_MOC_LITERAL(67, 1045, 11), // "getIFBANews"
QT_MOC_LITERAL(68, 1057, 7), // "newsUrl"
QT_MOC_LITERAL(69, 1065, 15), // "getPRPGINotices"
QT_MOC_LITERAL(70, 1081, 18), // "getStudentDocument"
QT_MOC_LITERAL(71, 1100, 12), // "documentName"
QT_MOC_LITERAL(72, 1113, 3), // "url"
QT_MOC_LITERAL(73, 1117, 15), // "getGradesReport"
QT_MOC_LITERAL(74, 1133, 22), // "getGradesReportDetails"
QT_MOC_LITERAL(75, 1156, 28), // "resetSEIPublicSearchAttempts"
QT_MOC_LITERAL(76, 1185, 22), // "prepareSEIPublicSearch"
QT_MOC_LITERAL(77, 1208, 12), // "emitPrepared"
QT_MOC_LITERAL(78, 1221, 16), // "searchSEIProcess"
QT_MOC_LITERAL(79, 1238, 13), // "processNumber"
QT_MOC_LITERAL(80, 1252, 7), // "captcha"
QT_MOC_LITERAL(81, 1260, 20), // "getSEIProcessDetails"
QT_MOC_LITERAL(82, 1281, 6), // "status"
QT_MOC_LITERAL(83, 1288, 6), // "Status"
QT_MOC_LITERAL(84, 1295, 12), // "sessionState"
QT_MOC_LITERAL(85, 1308, 12), // "SessionState"
QT_MOC_LITERAL(86, 1321, 8), // "userType"
QT_MOC_LITERAL(87, 1330, 8), // "UserType"
QT_MOC_LITERAL(88, 1339, 22), // "seiPublicSearchCaptcha"
QT_MOC_LITERAL(89, 1362, 4), // "Null"
QT_MOC_LITERAL(90, 1367, 7), // "Loading"
QT_MOC_LITERAL(91, 1375, 5), // "Ready"
QT_MOC_LITERAL(92, 1381, 5), // "Error"
QT_MOC_LITERAL(93, 1387, 9), // "LoggedOut"
QT_MOC_LITERAL(94, 1397, 8), // "LoggedIn"
QT_MOC_LITERAL(95, 1406, 9), // "Professor"
QT_MOC_LITERAL(96, 1416, 7) // "Student"

    },
    "NetworkController\0newVersionAvailable\0"
    "\0userAuthenticated\0statusChanged\0"
    "NetworkController::Status\0sessionStateChanged\0"
    "NetworkController::SessionState\0"
    "userTypeChanged\0NetworkController::UserType\0"
    "errorStringChanged\0errorString\0"
    "usernameChanged\0username\0myDataChanged\0"
    "myData\0termsChanged\0terms\0coursesChanged\0"
    "courses\0coursePartsChanged\0courseParts\0"
    "courseClassesChanged\0courseClasses\0"
    "courseStudentsChanged\0courseStudents\0"
    "IFBANewsChanged\0IFBANews\0PRPGINoticesChanged\0"
    "PRPGINotices\0newsChanged\0news\0"
    "gradesReportTermsChanged\0gradesReportTerms\0"
    "gradesReportChanged\0gradesReport\0"
    "gradesReportDetailsChanged\0"
    "gradesReportDetails\0seiPublicSearchCaptchaChanged\0"
    "seiPublicCaptcha\0seiProcessDetailsChanged\0"
    "seiProcessDetails\0seiPublicSearchPrepared\0"
    "seiProcessDetailsAvailable\0benchmarkGrades\0"
    "benchmarkAllNews\0benchmarkdetailsNews\0"
    "getBasicData\0getMyData\0getCourses\0"
    "term\0getCourseClasses\0courseId\0"
    "coursePartId\0getCourseStudents\0"
    "totalClasses\0registerUpdateClass\0hours\0"
    "date\0description\0previousPartId\0classId\0"
    "registerUpdateAttendance\0attendances\0"
    "partId\0removeClass\0index\0getIFBANews\0"
    "newsUrl\0getPRPGINotices\0getStudentDocument\0"
    "documentName\0url\0getGradesReport\0"
    "getGradesReportDetails\0"
    "resetSEIPublicSearchAttempts\0"
    "prepareSEIPublicSearch\0emitPrepared\0"
    "searchSEIProcess\0processNumber\0captcha\0"
    "getSEIProcessDetails\0status\0Status\0"
    "sessionState\0SessionState\0userType\0"
    "UserType\0seiPublicSearchCaptcha\0Null\0"
    "Loading\0Ready\0Error\0LoggedOut\0LoggedIn\0"
    "Professor\0Student"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
      19,  420, // properties
       3,  496, // enums/sets
       0,    0, // constructors
       0,       // flags
      23,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  254,    2, 0x06 /* Public */,
       3,    0,  255,    2, 0x06 /* Public */,
       4,    1,  256,    2, 0x06 /* Public */,
       6,    1,  259,    2, 0x06 /* Public */,
       8,    1,  262,    2, 0x06 /* Public */,
      10,    1,  265,    2, 0x06 /* Public */,
      12,    1,  268,    2, 0x06 /* Public */,
      14,    1,  271,    2, 0x06 /* Public */,
      16,    1,  274,    2, 0x06 /* Public */,
      18,    1,  277,    2, 0x06 /* Public */,
      20,    1,  280,    2, 0x06 /* Public */,
      22,    1,  283,    2, 0x06 /* Public */,
      24,    1,  286,    2, 0x06 /* Public */,
      26,    1,  289,    2, 0x06 /* Public */,
      28,    1,  292,    2, 0x06 /* Public */,
      30,    1,  295,    2, 0x06 /* Public */,
      32,    1,  298,    2, 0x06 /* Public */,
      34,    1,  301,    2, 0x06 /* Public */,
      36,    1,  304,    2, 0x06 /* Public */,
      38,    1,  307,    2, 0x06 /* Public */,
      40,    1,  310,    2, 0x06 /* Public */,
      42,    0,  313,    2, 0x06 /* Public */,
      43,    0,  314,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      44,    1,  315,    2, 0x0a /* Public */,
      45,    1,  318,    2, 0x0a /* Public */,
      46,    1,  321,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      47,    0,  324,    2, 0x02 /* Public */,
      48,    0,  325,    2, 0x02 /* Public */,
      49,    1,  326,    2, 0x02 /* Public */,
      51,    2,  329,    2, 0x02 /* Public */,
      51,    1,  334,    2, 0x22 /* Public | MethodCloned */,
      54,    3,  337,    2, 0x02 /* Public */,
      56,    7,  344,    2, 0x02 /* Public */,
      56,    6,  359,    2, 0x22 /* Public | MethodCloned */,
      62,    4,  372,    2, 0x02 /* Public */,
      65,    4,  381,    2, 0x02 /* Public */,
      67,    0,  390,    2, 0x02 /* Public */,
      67,    1,  391,    2, 0x02 /* Public */,
      69,    0,  394,    2, 0x02 /* Public */,
      70,    2,  395,    2, 0x02 /* Public */,
      73,    1,  400,    2, 0x02 /* Public */,
      73,    0,  403,    2, 0x22 /* Public | MethodCloned */,
      74,    1,  404,    2, 0x02 /* Public */,
      75,    0,  407,    2, 0x02 /* Public */,
      76,    1,  408,    2, 0x02 /* Public */,
      76,    0,  411,    2, 0x22 /* Public | MethodCloned */,
      78,    2,  412,    2, 0x02 /* Public */,
      81,    1,  417,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QJsonObject,   15,
    QMetaType::Void, QMetaType::QStringList,   17,
    QMetaType::Void, QMetaType::QJsonArray,   19,
    QMetaType::Void, QMetaType::QJsonArray,   21,
    QMetaType::Void, QMetaType::QJsonArray,   23,
    QMetaType::Void, QMetaType::QJsonArray,   25,
    QMetaType::Void, QMetaType::QJsonArray,   27,
    QMetaType::Void, QMetaType::QJsonArray,   29,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QStringList,   33,
    QMetaType::Void, QMetaType::QJsonArray,   35,
    QMetaType::Void, QMetaType::QJsonArray,   37,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void, QMetaType::QJsonObject,   41,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonArray,   35,
    QMetaType::Void, QMetaType::QJsonArray,   27,
    QMetaType::Void, QMetaType::QString,   31,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   52,   53,
    QMetaType::Void, QMetaType::QString,   52,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   52,   55,   53,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   52,   53,   57,   58,   59,   60,   61,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   52,   53,   57,   58,   59,   60,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap, QMetaType::QString, QMetaType::QString,   61,   63,   52,   64,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString,   61,   66,   52,   60,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   68,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   71,   72,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   72,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   77,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   79,   80,
    QMetaType::Void, QMetaType::QString,   72,

 // properties: name, type, flags
      82, 0x80000000 | 83, 0x00495009,
      84, 0x80000000 | 85, 0x00495009,
      86, 0x80000000 | 87, 0x00495009,
      11, QMetaType::QString, 0x00495001,
      13, QMetaType::QString, 0x00495001,
      15, QMetaType::QJsonObject, 0x00495001,
      17, QMetaType::QStringList, 0x00495001,
      19, QMetaType::QJsonArray, 0x00495001,
      21, QMetaType::QJsonArray, 0x00495001,
      23, QMetaType::QJsonArray, 0x00495001,
      25, QMetaType::QJsonArray, 0x00495001,
      27, QMetaType::QJsonArray, 0x00495001,
      29, QMetaType::QJsonArray, 0x00495001,
      31, QMetaType::QString, 0x00495001,
      33, QMetaType::QStringList, 0x00495001,
      35, QMetaType::QJsonArray, 0x00495001,
      37, QMetaType::QJsonArray, 0x00495001,
      88, QMetaType::QString, 0x00495001,
      41, QMetaType::QJsonObject, 0x00495001,

 // properties: notify_signal_id
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,
      11,
      12,
      13,
      14,
      15,
      16,
      17,
      18,
      19,
      20,

 // enums: name, alias, flags, count, data
      83,   83, 0x0,    4,  511,
      85,   85, 0x0,    2,  519,
      87,   87, 0x2,    2,  523,

 // enum data: key, value
      89, uint(NetworkController::Null),
      90, uint(NetworkController::Loading),
      91, uint(NetworkController::Ready),
      92, uint(NetworkController::Error),
      93, uint(NetworkController::LoggedOut),
      94, uint(NetworkController::LoggedIn),
      95, uint(NetworkController::UserType::Professor),
      96, uint(NetworkController::UserType::Student),

       0        // eod
};

void NetworkController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newVersionAvailable(); break;
        case 1: _t->userAuthenticated(); break;
        case 2: _t->statusChanged((*reinterpret_cast< NetworkController::Status(*)>(_a[1]))); break;
        case 3: _t->sessionStateChanged((*reinterpret_cast< NetworkController::SessionState(*)>(_a[1]))); break;
        case 4: _t->userTypeChanged((*reinterpret_cast< NetworkController::UserType(*)>(_a[1]))); break;
        case 5: _t->errorStringChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->usernameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->myDataChanged((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 8: _t->termsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 9: _t->coursesChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 10: _t->coursePartsChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 11: _t->courseClassesChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 12: _t->courseStudentsChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 13: _t->IFBANewsChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 14: _t->PRPGINoticesChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 15: _t->newsChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->gradesReportTermsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 17: _t->gradesReportChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 18: _t->gradesReportDetailsChanged((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 19: _t->seiPublicSearchCaptchaChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->seiProcessDetailsChanged((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 21: _t->seiPublicSearchPrepared(); break;
        case 22: _t->seiProcessDetailsAvailable(); break;
        case 23: _t->benchmarkGrades((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 24: _t->benchmarkAllNews((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 25: _t->benchmarkdetailsNews((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->getBasicData(); break;
        case 27: _t->getMyData(); break;
        case 28: _t->getCourses((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: _t->getCourseClasses((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 30: _t->getCourseClasses((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: _t->getCourseStudents((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 32: _t->registerUpdateClass((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 33: _t->registerUpdateClass((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6]))); break;
        case 34: _t->registerUpdateAttendance((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 35: _t->removeClass((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 36: _t->getIFBANews(); break;
        case 37: _t->getIFBANews((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 38: _t->getPRPGINotices(); break;
        case 39: _t->getStudentDocument((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 40: _t->getGradesReport((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->getGradesReport(); break;
        case 42: _t->getGradesReportDetails((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 43: _t->resetSEIPublicSearchAttempts(); break;
        case 44: _t->prepareSEIPublicSearch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->prepareSEIPublicSearch(); break;
        case 46: _t->searchSEIProcess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 47: _t->getSEIProcessDetails((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::newVersionAvailable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::userAuthenticated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(NetworkController::Status );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::statusChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(NetworkController::SessionState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::sessionStateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(NetworkController::UserType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::userTypeChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::errorStringChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::usernameChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::myDataChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::termsChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::coursesChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::coursePartsChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::courseClassesChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::courseStudentsChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::IFBANewsChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::PRPGINoticesChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::newsChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::gradesReportTermsChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::gradesReportChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::gradesReportDetailsChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::seiPublicSearchCaptchaChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::seiProcessDetailsChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::seiPublicSearchPrepared)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (NetworkController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkController::seiProcessDetailsAvailable)) {
                *result = 22;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<NetworkController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Status*>(_v) = _t->status(); break;
        case 1: *reinterpret_cast< SessionState*>(_v) = _t->sessionState(); break;
        case 2: *reinterpret_cast< UserType*>(_v) = _t->userType(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->errorString(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->username(); break;
        case 5: *reinterpret_cast< QJsonObject*>(_v) = _t->myData(); break;
        case 6: *reinterpret_cast< QStringList*>(_v) = _t->terms(); break;
        case 7: *reinterpret_cast< QJsonArray*>(_v) = _t->courses(); break;
        case 8: *reinterpret_cast< QJsonArray*>(_v) = _t->courseParts(); break;
        case 9: *reinterpret_cast< QJsonArray*>(_v) = _t->courseClasses(); break;
        case 10: *reinterpret_cast< QJsonArray*>(_v) = _t->courseStudents(); break;
        case 11: *reinterpret_cast< QJsonArray*>(_v) = _t->IFBANews(); break;
        case 12: *reinterpret_cast< QJsonArray*>(_v) = _t->PRPGINotices(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->news(); break;
        case 14: *reinterpret_cast< QStringList*>(_v) = _t->gradesReportTerms(); break;
        case 15: *reinterpret_cast< QJsonArray*>(_v) = _t->gradesReport(); break;
        case 16: *reinterpret_cast< QJsonArray*>(_v) = _t->gradesReportDetails(); break;
        case 17: *reinterpret_cast< QString*>(_v) = _t->seiPublicSearchCaptcha(); break;
        case 18: *reinterpret_cast< QJsonObject*>(_v) = _t->seiProcessDetails(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject NetworkController::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NetworkController.data,
    qt_meta_data_NetworkController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 48)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 48;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 19;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void NetworkController::newVersionAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NetworkController::userAuthenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NetworkController::statusChanged(NetworkController::Status _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetworkController::sessionStateChanged(NetworkController::SessionState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NetworkController::userTypeChanged(NetworkController::UserType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NetworkController::errorStringChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NetworkController::usernameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void NetworkController::myDataChanged(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void NetworkController::termsChanged(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void NetworkController::coursesChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void NetworkController::coursePartsChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void NetworkController::courseClassesChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void NetworkController::courseStudentsChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void NetworkController::IFBANewsChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void NetworkController::PRPGINoticesChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void NetworkController::newsChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void NetworkController::gradesReportTermsChanged(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void NetworkController::gradesReportChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void NetworkController::gradesReportDetailsChanged(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void NetworkController::seiPublicSearchCaptchaChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void NetworkController::seiProcessDetailsChanged(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void NetworkController::seiPublicSearchPrepared()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void NetworkController::seiProcessDetailsAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
