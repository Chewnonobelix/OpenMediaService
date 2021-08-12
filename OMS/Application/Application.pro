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

smart.commands += $$quote(cmd /c xcopy /Y /S /I $$shell_path($${PWD}//..//Rules//*.json) $$shell_path($${OUT_PWD}//Rules))
tr.commands += $$quote(cmd /c xcopy /Y /S /I $$shell_path($${PWD}//..//Tr//*.qm) $$shell_path($${OUT_PWD}//Tr))

QMAKE_EXTRA_TARGETS += smart tr
POST_TARGETDEPS += smart tr
