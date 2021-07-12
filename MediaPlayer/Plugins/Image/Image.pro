DEFINES += IMAGE_LIBRARY
TARGET = Image
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Image
SOURCES += \
	controllerimage.cpp \
	image_plugin.cpp \
	imagelistmodel.cpp \
	librairyimagemodel.cpp

HEADERS += \
    controllerimage.h \
    image_global.h \
    image_plugin.h \
    imagelistmodel.h \
    librairyimagemodel.h

# Default rules for deployment.
include(../global.pri)

RESOURCES += \
	image.qrc

DISTFILES += \
    imagerules.json
