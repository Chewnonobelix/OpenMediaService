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

unix: {
    QML_DIR = $$OUT_PWD/../../Application/Ux/MediaPlayer/$$NAME
    PLUGINS_DIR = $$OUT_PWD/../../Application/Plugins/
    MAKE_DIR.commands = mkdir -p $$QML_DIR $$PLUGINS_DIR | true
    copy_qmldir.commands = "cp -r $$_PRO_FILE_PWD_/qmldir $$QML_DIR/qmldir"
    copy_libs.commands = "cp -r $$OUT_PWD/*.so $$PLUGINS_DIR | true"
    qml_libs.commands = "cp -r $$OUT_PWD/*.so $$QML_DIR | true"

     QMAKE_EXTRA_TARGETS += MAKE_DIR
     QMAKE_EXTRA_TARGETS += copy_qmldir copy_libs qml_libs
     PRE_TARGETDEPS += MAKE_DIR copy_qmldir
     QMAKE_POST_LINK = $$copy_libs.commands | $$qml_libs.commands
}

QML_IMPORT_MAJOR_VERSION = 1
QML_IMPORT_NAME = MediaPlayer.$$NAME
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $${OUT_PWD}/../../Application/Ux

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $${OUT_PWD}/../../Application/Ux

DISTFILES = qmldir
#DESTDIR += $$OUT_PWD/../../Application/Plugins
qmldir.files = qmldir
unix {
		installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
		qmldir.path = $$installPath
		target.path = $$installPath
                INSTALLS += target qmldir
}

INCLUDEPATH = $$PWD/../Core $$PWD/../3rdParty/xml2json/include
DEPENDPATH = $$OUT_PWD/../../Application

win32: {
    LIBS += -L$$OUT_PWD/../../DesignLibrary/DesignPattern/debug -lDesignPattern
    LIBS += -L$$OUT_PWD/../../ExpressionLibrary/LibExpression/debug -lLibExpression
    LIBS += -L$$OUT_PWD/../../Application/Ux -lUxComponents
    LIBS = -L$$OUT_PWD/../../Application -lLibMediaPlayerCore
}
else:unix: {
    LIBS += -L$$OUT_PWD/../../DesignLibrary/DesignPattern/ -lDesignPattern
    LIBS += -L$$OUT_PWD/../../ExpressionLibrary/LibExpression/ -lLibExpression
    LIBS += -L$$OUT_PWD/../../Application/Ux/MediaPlayer/Components/ -lUxComponents
    LIBS = -L$$OUT_PWD/../../Application -lLibMediaPlayerCore
}

INCLUDEPATH += $$PWD/../DesignLibrary/DesignPattern $$PWD/../ExpressionLibrary/LibExpression $$PWD/../UxComponent


LIBS += -L$$OUT_PWD/../../DesignLibrary/DesignPattern/ -lDesignPattern
LIBS += -L$$OUT_PWD/../../ExpressionLibrary/LibExpression/ -lLibExpression
LIBS += -L$$OUT_PWD/../../Application/Ux/MediaPlayer/Components -lUxComponents

