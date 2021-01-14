QT += qml quick core

TEMPLATE = lib

CONFIG += c++17 plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
		target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR += $$OUT_PWD/../../Application/Ux/MediaPlayer/$$NAME

message($$DESTDIR)
!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
		copy_qmldir.target = $$DESTDIR/qmldir
		copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
		copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
		QMAKE_EXTRA_TARGETS += copy_qmldir
		PRE_TARGETDEPS += $$copy_qmldir.target
}

QML_IMPORT_MAJOR_VERSION = 1
QML_IMPORT_NAME = MediaPlayer.$$NAME

DISTFILES = qmldir
DLLDESTDIR += $$OUT_PWD/../../Application/Plugins

qmldir.files = qmldir
unix {
		installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
		qmldir.path = $$installPath
		target.path = $$installPath
		INSTALLS += target qmldir
}
