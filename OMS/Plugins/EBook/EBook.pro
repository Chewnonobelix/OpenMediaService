DEFINES += EBOOK_LIBRARY


TARGET = EBook
TARGET = $$qtLibraryTarget($$TARGET)
NAME = EBook

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controllerebook.cpp \
    ebook_plugin.cpp

HEADERS += \
    EBook_global.h \
    controllerebook.h \
    ebook_plugin.h

include(../global.pri)
