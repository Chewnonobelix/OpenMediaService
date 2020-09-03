#include "Controller/controllermain.h"
#include <QGuiApplication>

int main (int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    ControllerMain cm;
    cm.exec();
    return app.exec();
}
