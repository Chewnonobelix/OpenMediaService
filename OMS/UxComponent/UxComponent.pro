TEMPLATE = lib
TARGET = UxComponents
QT += qml quick
CONFIG += plugin c++17

TARGET = $$qtLibraryTarget($$TARGET)
uri = MediaPlayer.Components

QML_IMPORT_NAME = MediaPlayer.Components
QML_IMPORT_MAJOR_VERSION = 1

# Input
SOURCES += \
        UxComponent_plugin.cpp

HEADERS += \
        UxComponent_plugin.hpp

DISTFILES = qmldir
DLLDESTDIR += $$OUT_PWD/../Application/Ux

DESTDIR += $$OUT_PWD/../Application/Ux/MediaPlayer/Components

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$DESTDIR/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath $$OUT_PWD/../Application/Ux
    INSTALLS += target qmldir
}

RESOURCES += \
	ux.qrc

unix: {
#    POST_TARGETDEPS += cp $$OUT_PWD/../Application/Ux/MediaPlayer/Components $$OUT_PWD/../Application/Ux
}
