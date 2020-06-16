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
    getroomtemperaturecontroller.cpp \
    global.cpp \
    main.cpp \
    managerlogincontroller.cpp \
    managerloginwidget.cpp \
    master_request_controller.cpp \
    monitordialog.cpp \
    scheduleinfocontroller.cpp \
    setmodecontroller.cpp \
    standbywidget.cpp \
    managercontrolpanel.cpp \
    manager.cpp \
    useandcost.cpp \
    useandcostcontrollermaster.cpp \
    userlogincontroller.cpp \
    usermanagementwidget.cpp \
    userinfocontroller.cpp \
    airsupplycontroller.cpp \
    schedule.cpp \
    report.cpp \
    usersetspeedcontroller.cpp \
    usersettemperaturecontroller.cpp \
    usershutdowncontroller.cpp \
    reportwidget.cpp\
    detailwidget.cpp

HEADERS += \
    getroomtemperaturecontroller.h \
    global.h \
    listener.h \
    managerlogincontroller.h \
    managerloginwidget.h \
    master_request_controller.h \
    monitordialog.h \
    scheduleinfocontroller.h \
    setmodecontroller.h \
    standbywidget.h \
    managercontrolpanel.h \
    manager.h \
    useandcost.h \
    useandcostcontrollermaster.h \
    userlogincontroller.h \
    usermanagementwidget.h \
    userinfocontroller.h \
    airsupplycontroller.h \
    schedule.h \
    report.h \
    usersetspeedcontroller.h \
    usersettemperaturecontroller.h \
    usershutdowncontroller.h \
    reportwidget.h\
    detailwidget.h

FORMS += \
    managerloginwidget.ui \
    monitordialog.ui \
    standbywidget.ui \
    managercontrolpanel.ui \
    usermanagementwidget.ui \
    reportwidget.ui\
    detailwidget.ui

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
