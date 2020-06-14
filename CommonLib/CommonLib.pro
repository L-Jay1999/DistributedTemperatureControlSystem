QT -= gui
QT += network sql

TEMPLATE = lib
CONFIG += staticlib

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
    common.cpp \
    config.cpp \
    database_defs.cpp \
    dbaccess.cpp \
    dbhelper.cpp \
    log.cpp \
    request_controller.cpp \
    request_payload.cpp

HEADERS += \
    common.h \
    database_defs.h \
    dbaccess.h \
    dbhelper.h \
    listener.h \
    log.h \
    msg_queen.h \
    request_base.h \
    request_controller.h \
    request_payload.h \
    requests.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
