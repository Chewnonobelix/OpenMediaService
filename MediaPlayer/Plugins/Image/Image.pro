DEFINES += IMAGE_LIBRARY
TARGET = Image
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Image
SOURCES +=

HEADERS += \
    Image_global.hpp

# Default rules for deployment.
include(../global.pri)
