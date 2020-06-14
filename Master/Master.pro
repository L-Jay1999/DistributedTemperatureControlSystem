#-------------------------------------------------
#
# Project created by QtCreator 2020-06-09T15:00:18
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

lessThan(QT_MINOR_VERSION, 12) {
    contains(QMAKE_COMPILER_DEFINES, __MSC_VER) {
        QMAKE_CXXFLAGS += /std:c++17
    }
    else {
        QMAKE_CXXFLAGS += -std=c++17
    }
}
else {
    CONFIG += c++17
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    global.cpp \
        main.cpp \
    managerlogincontroller.cpp \
    managerloginwidget.cpp \
    standbywidget.cpp \
    managercontrolpanel.cpp \
    manager.cpp \
    powersupplywidget.cpp \
    operationconfirmationdialog.cpp \
    usermanagementwidget.cpp \
    promptdialog.cpp \
    requestcontroller.cpp \
    userinfocontroller.cpp \
    airsupplycontroller.cpp \
    schedule.cpp \
    parameterwidget.cpp \
    monitorwidget.cpp \
    report.cpp

HEADERS += \
    global.h \
    managerlogincontroller.h \
    managerloginwidget.h \
    standbywidget.h \
    managercontrolpanel.h \
    manager.h \
    powersupplywidget.h \
    operationconfirmationdialog.h \
    usermanagementwidget.h \
    promptdialog.h \
    requestcontroller.h \
    userinfocontroller.h \
    airsupplycontroller.h \
    schedule.h \
    parameterwidget.h \
    monitorwidget.h \
    report.h

FORMS += \
    managerloginwidget.ui \
    standbywidget.ui \
    managercontrolpanel.ui \
    powersupplywidget.ui \
    operationconfirmationdialog.ui \
    usermanagementwidget.ui \
    promptdialog.ui \
    parameterwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CommonLib/release/ -lCommonLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CommonLib/debug/ -lCommonLib
else:unix: LIBS += -L$$OUT_PWD/../CommonLib/ -lCommonLib

INCLUDEPATH += $$PWD/../CommonLib
DEPENDPATH += $$PWD/../CommonLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonLib/release/libCommonLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonLib/debug/libCommonLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonLib/release/CommonLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonLib/debug/CommonLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CommonLib/libCommonLib.a
