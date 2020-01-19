QT       += core websockets
QT       -= gui

TARGET = wsclient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    controller.cpp \
    main.cpp \
    ws2client.cpp

HEADERS += \
    controller.h \
    ws2client.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
