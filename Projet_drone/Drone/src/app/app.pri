INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD


WIDGETS_DIR = "$$PWD/widgets"

INCLUDEPATH += \
    $$PWD/cmp/thread_element/

SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainwindow.cpp \
    $$PWD/cmp/thread_element/thread_element.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/cmp/thread_element/thread_element.h

FORMS += \
    $$PWD/mainwindow.ui

RESOURCES += \

DISTFILES += \
