QT += quick xml core qml

CONFIG += c++latest

INCLUDEPATH += ../DesignLibrary/DesignPattern ../ExpressionLibrary/LibExpression ../Core

TARGET = OpenMediaService

LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/debug -lDesignPattern
LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/debug -lLibExpression
LIBS += -L$$OUT_PWD/ -lLibMediaPlayerCore
LIBS += -L$$OUT_PWD/Ux -lUxComponents

SOURCES += \
    main.cpp

