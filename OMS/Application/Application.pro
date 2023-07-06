QT += quick xml core qml sql

CONFIG += c++17

INCLUDEPATH += ../DesignLibrary/DesignPattern ../ExpressionLibrary/LibExpression ../Core

TARGET = OpenMediaService

win32: {
    LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/debug -lDesignPattern
    LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/debug -lLibExpression
    LIBS += -L$$OUT_PWD/ -lLibMediaPlayerCore
    LIBS += -L$$OUT_PWD/Ux -lUxComponents
}
else:unix: {
    LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/ -lDesignPattern
    LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/ -lLibExpression
    LIBS += -L$$OUT_PWD/../Application/Ux/MediaPlayer/Components -lUxComponents
    LIBS += -L$$OUT_PWD/ -lLibMediaPlayerCore
}

SOURCES += \
    main.cpp
