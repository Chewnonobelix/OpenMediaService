#include <QGuiApplication>
#include <QtGlobal>

#include "Controller/Core/controllermain.h"


int main(int argc, char **argv) {

    qSetMessagePattern("%{type} %{time h:mm:ss} %{function} (%{line}) \"%{category}\" #%{message}#");

	QGuiApplication app(argc, argv);
	ControllerMain cm;
	cm.exec();
	return app.exec();
}
