QT -= gui

CONFIG += c++latest console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        testexp.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/release/ -lLibExpression
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ExpressionLibrary/LibExpression/debug/ -lLibExpression

INCLUDEPATH += $$PWD/../ExpressionLibrary/LibExpression
DEPENDPATH += $$PWD/../ExpressionLibrary/LibExpression

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/release/ -lDesignPattern
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DesignLibrary/DesignPattern/debug/ -lDesignPattern

INCLUDEPATH += $$PWD/../DesignLibrary/DesignPattern
DEPENDPATH += $$PWD/../DesignLibrary/DesignPattern

HEADERS += \
    testexp.h
