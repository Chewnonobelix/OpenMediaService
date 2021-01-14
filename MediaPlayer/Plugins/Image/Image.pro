DEFINES += IMAGE_LIBRARY
TARGET = Image
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Image
SOURCES += \
	ControllerImage.cpp \
	Image_plugin.cpp

HEADERS += \
    ControllerImage.hpp \
    Image_global.hpp \
    Image_plugin.hpp

# Default rules for deployment.
include(../global.pri)

RESOURCES += \
	image.qrc
