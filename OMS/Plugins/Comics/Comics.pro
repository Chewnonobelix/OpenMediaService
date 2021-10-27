DEFINES += COMICS_LIBRARY


TARGET = Comics
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Comics

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comics_plugin.cpp \
    controllercomics.cpp

HEADERS += \
    Comics_global.h \
    comics_plugin.h \
    controllercomics.h

include(../global.pri)

RESOURCES += \
    comics.qrc
