DEFINES += AUDIO_LIBRARY


TARGET = Audio
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Audio

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audio_plugin.cpp \
    controlleraudio.cpp

HEADERS += \
    Audio_global.h \
    audio_plugin.h \
    controlleraudio.h

include(../global.pri)

# Default rules for deployment.

RESOURCES += \
    audio.qrc
