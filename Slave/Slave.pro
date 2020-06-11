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
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    userloginwidget.cpp \
    slavecontrolwindow.cpp \
    logincontroller.cpp \
    setspeedcontroller.cpp \
    settemperaturecontroller.cpp \
    useandcostcontroller.cpp \
    getinformationcontroller.cpp \
    gettemperaturecontroller.cpp \
    modealtercontroller.cpp \
    windcontroller.cpp \
    shutdowncontroller.cpp \
    user.cpp

HEADERS += \
    userloginwidget.h \
    slavecontrolwindow.h \
    logincontroller.h \
    setspeedcontroller.h \
    settemperaturecontroller.h \
    useandcostcontroller.h \
    getinformationcontroller.h \
    gettemperaturecontroller.h \
    modealtercontroller.h \
    windcontroller.h \
    shutdowncontroller.h \
    user.h

win32 {
    LIBS += ../lib/CommonLib.lib
}

FORMS += \
    userloginwidget.ui \
    slavecontrolwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
