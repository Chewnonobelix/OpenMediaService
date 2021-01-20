#include <QGuiApplication>

#include "Controller/Core/controllermain.h"

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);
	ControllerMain cm;
	cm.exec();
	return app.exec();
}
