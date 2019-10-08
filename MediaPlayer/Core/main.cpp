#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Controller/controllermain.h"
#include "Controller/xmldatabase.h"
#include <QTime>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
    QGuiApplication app(argc, argv);
    qRegisterMetaType<XmlDatabase>();
    
    qDebug()<<QMetaType::type("XmlDatabase");    

    ControllerMain cm;
    
    return app.exec();
}
