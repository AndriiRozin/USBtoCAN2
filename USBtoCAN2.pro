#-------------------------------------------------
#
# Project created by QtCreator 2018-10-04T20:59:21
#
#-------------------------------------------------

QT       += core gui widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USBtoCAN2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    hmi.cpp \
    hmi/hmi_info.cpp \
    hmi/hmi_transmit.cpp \
    hmi/hmi_monitor.cpp \
    hmi/hmi_status.cpp \
    hmi/hmi_filter.cpp \
    process_message/process_info.cpp \
    process_message/process_error.cpp \
    process_message/process_tx.cpp \
    process_message/process_monitor.cpp \
    process_message.cpp \
    inp_devices.cpp \
    inp_devices/inp_file.cpp \
    inp_devices/inp_serial.cpp \
    config.cpp

HEADERS += \
        mainwindow.h \
    hmi.h \
    hmi/hmi_info.h \
    hmi/hmi_transmit.h \
    hmi/hmi_monitor.h \
    hmi/hmi_status.h \
    hmi/hmi_filter.h \
    process_message/process_info.h \
    process_message/process_error.h \
    process_message/process_tx.h \
    process_message/process_monitor.h \
    process_message.h \
    inp_devices.h \
    inp_devices/inp_file.h \
    inp_devices/inp_serial.h \
    config.h

FORMS += \
        mainwindow.ui \
    config.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
