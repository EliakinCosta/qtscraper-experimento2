#include "core.h"

#include "networkcontroller.h"

#ifdef Q_OS_ANDROID

#include <QAndroidJniObject>
#include <jni.h>
#include <qsettings.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
  Java_br_edu_ifba_gsort_emile_WebViewActivity_sendCookies(JNIEnv *env, jobject obj, jstring newCookies)
{
    Q_UNUSED(obj)
//    qDebug() << "Cookies sent:" << env->GetStringUTFChars(newCookies, nullptr);
    QString cookies(env->GetStringUTFChars(newCookies, nullptr));
    Core::instance()->networkController()->setCookies(cookies);
    QSettings settings("ifba", "emile-cookies");
    settings.setValue("cookies", cookies);
    QMetaObject::invokeMethod(Core::instance()->networkController(), "getBasicData", Qt::QueuedConnection);
}

#ifdef __cplusplus
}
#endif

#endif

Core *Core::_instance = nullptr;

Core::Core(QObject *parent)
    : QObject(parent),
      _networkController(new NetworkController(this))
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject::callStaticMethod<void>("br/edu/ifba/gsort/emile/WebViewController",
                                        "disableDeathOnFileUriExposure");
#endif
}

Core::~Core()
{
    delete _networkController;
}

Core *Core::instance()
{
    if (!_instance)
        _instance = new Core;
    return _instance;
}

NetworkController *Core::networkController() const
{
    return _networkController;
}

QString Core::version() const
{
    return QStringLiteral(VERSION);
}
