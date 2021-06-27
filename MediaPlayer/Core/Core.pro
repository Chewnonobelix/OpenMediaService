QT += quick xml core qml

CONFIG += c++17

TEMPLATE = lib
DEFINES += MEDIAPLAYERCORE_LIBRARY
TARGET = LibMediaPlayerCore
DLLDESTDIR = $$OUT_PWD/../Application/
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Controller/Core/abstractcontroller.cpp \
        Controller/Core/controllerlibrary.cpp \
        Controller/Core/controllermain.cpp \
        Controller/Core/tabmanager.cpp \
        Controller/Core/tabwrapper.cpp \
        Controller/Data/datajson.cpp \
        Controller/Data/dataxml.cpp \
        Controller/Data/interfacesaver.cpp \
        Controller/DataModel/librarydatamodel.cpp \
        Controller/DataModel/playlistmodel.cpp \
        Controller/DataModel/smartmodel.cpp \
        Controller/Plugins/interfaceplugins.cpp \
        Controller/Plugins/pluginmanager.cpp \
        Model/Expression/endexpression.cpp \
        Model/Expression/startexpression.cpp \
        Model/Expression/variantsuperiorexpression.cpp \
        Model/smartplaylist.cpp \
        Model\global.cpp \
        Model\library.cpp \
        Model\libraryprobe.cpp \
        Model\media.cpp \
        Model\playlist.cpp \
        Controller/Core/controllersettings.cpp

RESOURCES += View\qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = "$${OUT_PWD}/../Application/Ux"

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$QML_IMPORT_PATH

DEFINES += QT_DEPRECATED_WARNINGS QML_SOURCE=\\\"$$PWD\\\" QML_IMPORT_PATH=\\\"$$QML_IMPORT_PATH\\\"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Controller/Core/abstractcontroller.h \
    Controller/Core/controllerlibrary.h \
    Controller/Core/controllermain.h \
    Controller/Core/tabmanager.h \
    Controller/Core/tabwrapper.h \
    Controller/Data/datajson.h \
    Controller/Data/dataxml.h \
    Controller/Data/interfacesaver.h \
    Controller/DataModel/librarydatamodel.h \
    Controller/DataModel/playlistmodel.h \
    Controller/DataModel/smartmodel.h \
    Controller/Plugins/interfaceplugins.h \
    Controller/Plugins/pluginmanager.h \
    Model/Expression/endexpression.h \
    Model/Expression/startexpression.h \
    Model/Expression/variantsuperiorexpression.h \
    Model/smartplaylist.h \
    Model\global.h \
    Model\library.h \
    Model\libraryprobe.h \
    Model\media.h \
    Model\playlist.h \
    Controller/Core/controllersettings.h \
    mediaplayercore_global.h


INCLUDEPATH += $$PWD/../DesignLibrary/DesignPattern $$PWD/../ExpressionLibrary/LibExpression $$PWD/../UxComponent


LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/debug -lDesignPattern
LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/debug -lLibExpression
LIBS += -L$$OUT_PWD/../Application/Ux -lUxComponents

