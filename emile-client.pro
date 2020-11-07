QT += quick network xmlpatterns
android: QT += androidextras

CONFIG += c++17
LIBS += -ltidy

android: INCLUDEPATH += ./tidy-html5/include/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core.cpp \
    main.cpp \
    networkcontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/libs/arm64-v8a/libtidy.so \
        $$PWD/libs/arm64-v8a/libcrypto_1_1.so \
        $$PWD/libs/arm64-v8a/libssl_1_1.so
    LIBS += -L$$PWD/libs/arm64-v8a/

    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/libs/armeabi-v7a/libtidy.so \
        $$PWD/libs/armeabi-v7a/libcrypto_1_1.so \
        $$PWD/libs/armeabi-v7a/libssl_1_1.so
    LIBS += -L$$PWD/libs/armeabi-v7a/

    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

HEADERS += \
    core.h \
    networkcontroller.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/src/br/edu/ifba/gsort/emile/WebViewController.java \
    android/src/br/edu/ifba/gsort/emile/WebViewActivity.java \
    android/res/values/libs.xml

defineReplace(droidVersionCode) {
        segments = $$split(1, ".")
        for (segment, segments): vCode = "$$first(vCode)$$format_number($$segment, width=3 zeropad)"
        contains(ANDROID_TARGET_ARCH, arm64-v8a): \
            suffix = 1
        else:contains(ANDROID_TARGET_ARCH, armeabi-v7a): \
            suffix = 0

        # add more cases as needed
        return($$first(vCode)$$first(suffix))
}

VERSION = 0.5.0
ANDROID_VERSION_NAME = $$VERSION
ANDROID_VERSION_CODE = $$droidVersionCode($$ANDROID_VERSION_NAME)

SOURCE_VERSION = $$system("fgrep VERSION core.h | cut -d' ' -f3" | cut -d'\\"' -f2)
!equals(VERSION, $$SOURCE_VERSION) {
    message($$VERSION != $$SOURCE_VERSION)
    error("Versions difer! Check VERSION variable in emile-client.pro and SOURCE_VERSION define in core.h")
}

