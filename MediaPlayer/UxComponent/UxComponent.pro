TEMPLATE = lib
TARGET = UxComponents
QT += qml quick
CONFIG += plugin c++17

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.chewnonobelix.MediaPlayer.Components

# Input
SOURCES += \
        UxComponent_plugin.cpp

HEADERS += \
        UxComponent_plugin.hpp

DISTFILES = qmldir

DESTDIR += $$OUT_PWD/../Application/Ui

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
    target.path = $$installPath
    INSTALLS += target qmldir
}
