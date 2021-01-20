DEFINES += VIDEO_LIBRARY
TARGET = Video
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Video
SOURCES += \
	ControllerVideo.cpp \
	Video_plugin.cpp

HEADERS += \
		ControllerVideo.hpp \
		Video_global.hpp \
		Video_plugin.hpp

# Default rules for deployment.
include(../global.pri)

RESOURCES += \
	video.qrc
