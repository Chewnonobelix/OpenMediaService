#include <QGuiApplication>
#include <QtGlobal>

#include "Controller/Core/controllermain.h"


int main(int argc, char **argv) {

    qSetMessagePattern("%{type} %{message} %{time yyyyMMdd h:mm:ss} %{file} %{function} %{line} %{category}");

	QGuiApplication app(argc, argv);
	ControllerMain cm;
	cm.exec();
	return app.exec();
}
