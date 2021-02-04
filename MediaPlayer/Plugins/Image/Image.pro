DEFINES += IMAGE_LIBRARY
TARGET = Image
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Image
SOURCES += \
	controllerimage.cpp \
	image_plugin.cpp \
	imagemodel.cpp

HEADERS += \
    controllerimage.h \
    image_global.h \
    image_plugin.h \
    imagemodel.h

# Default rules for deployment.
include(../global.pri)

RESOURCES += \
	image.qrc
