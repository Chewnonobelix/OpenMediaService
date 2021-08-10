DEFINES += VIDEO_LIBRARY
TARGET = Video
TARGET = $$qtLibraryTarget($$TARGET)
NAME = Video
SOURCES += \
	controllervideo.cpp \
	video_plugin.cpp

HEADERS += \
		controllervideo.h \
		video_global.h \
		video_plugin.h

# Default rules for deployment.
include(../global.pri)

RESOURCES += \
	video.qrc
