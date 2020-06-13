cmake_minimum_required(VERSION 3.16)
project(DC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories(CommonLib)
include_directories(Master)
include_directories(Slave)
find_package(Qt5Widgets REQUIRED)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.9.9\\mingw53_32\\")
add_executable(DC
        CommonLib/common.cpp
        CommonLib/common.h
        CommonLib/config.cpp
        CommonLib/database_defs.cpp
        CommonLib/database_defs.h
        CommonLib/dbaccess.cpp
        CommonLib/dbaccess.h
        CommonLib/dbhelper.cpp
        CommonLib/dbhelper.h
        CommonLib/listener.h
        CommonLib/log.cpp
        CommonLib/log.h
        CommonLib/request_base.h
        CommonLib/request_controller.h
        CommonLib/request_payload.cpp
        CommonLib/request_payload.h
        CommonLib/requests.h
        Master/main.cpp
        Master/mainwindow.cpp
        Master/mainwindow.h
        Master/manager.cpp
        Master/manager.h
        Master/managercontrolpanel.cpp
        Master/managercontrolpanel.h
        Master/managerlogincontroller.cpp
        Master/managerlogincontroller.h
        Master/managerloginwidget.cpp
        Master/managerloginwidget.h
        Master/standbywidget.cpp
        Master/standbywidget.h
        Slave/getinformationcontroller.cpp
        Slave/getinformationcontroller.h
        Slave/gettemperaturecontroller.cpp
        Slave/gettemperaturecontroller.h
        Slave/logincontroller.cpp
        Slave/logincontroller.h
        Slave/main.cpp
        Slave/modealtercontroller.cpp
        Slave/modealtercontroller.h
        Slave/setspeedcontroller.cpp
        Slave/setspeedcontroller.h
        Slave/settemperaturecontroller.cpp
        Slave/settemperaturecontroller.h
        Slave/shutdowncontroller.cpp
        Slave/shutdowncontroller.h
        Slave/slavecontrolwindow.cpp
        Slave/slavecontrolwindow.h
        Slave/useandcostcontroller.cpp
        Slave/useandcostcontroller.h
        Slave/user.cpp
        Slave/user.h
        Slave/userloginwidget.cpp
        Slave/userloginwidget.h
        Slave/windcontroller.cpp
        Slave/windcontroller.h)

target_link_libraries(DC Qt5::Widgets)


