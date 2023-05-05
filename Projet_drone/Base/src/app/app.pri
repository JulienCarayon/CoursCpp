INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD


WIDGETS_DIR = "$$PWD/widgets"

INCLUDEPATH += \
    $$PWD/lib/paho.mqtt.cpp/
#    $$PWD/cmp/thread_element/


SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainwindow.cpp \
    $$PWD/lib/paho.mqtt.cpp/src/*.cpp \
    $$PWD/mqttManager.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/lib/paho.mqtt.cpp/src/mqtt \
    $$PWD/mqttManager.h

FORMS += \
    $$PWD/mainwindow.ui

RESOURCES += \
    $$PWD/resources.qrc
DISTFILES += \

LIBS += -L$$PWD/lib/paho.mqtt.cpp/ -lpaho-mqttpp3 -lpaho-mqtt3as
