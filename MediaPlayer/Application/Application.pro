QT += quick xml core qml

CONFIG += c++17

INCLUDEPATH += ../DesignLibrary/DesignPattern ../ExpressionLibrary/LibExpression ../Core


LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/debug -lDesignPattern
LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/debug -lLibExpression
LIBS += -L$$OUT_PWD/debug -lLibMediaPlayerCore
LIBS += -L$$OUT_PWD/Ui -lUxComponents

SOURCES += \
    main.cpp

