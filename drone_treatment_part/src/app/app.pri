INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD


WIDGETS_DIR = "$$PWD/widgets"

INCLUDEPATH += \
    $$PWD/lib/paho.mqtt.cpp/

SOURCES += \
    $$PWD/main.cpp\
    $$PWD/lib/paho.mqtt.cpp/src/*cpp

HEADERS += \

FORMS += \

RESOURCES += \

DISTFILES += \

LIBS += -L$$PWD/lib/paho.mqtt.cpp/ -lpaho-mqttpp3 -lpaho-mqtt3as
