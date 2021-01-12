QT += testlib xml core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++17
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../DesignLibrary/DesignPattern ../../ExpressionLibrary/LibExpression ../../Core/
LIBS += -L$$OUT_PWD/../../DesignLibrary/DesignPattern/debug -lDesignPattern
LIBS += -L$$OUT_PWD/../../ExpressionLibrary/LibExpression/debug -lLibExpression
LIBS += -L$$OUT_PWD/../../Core/debug -lLibMediaPlayerCore

DEFINES += TESTDATA=\\\"$${PWD}/Data\\\"
