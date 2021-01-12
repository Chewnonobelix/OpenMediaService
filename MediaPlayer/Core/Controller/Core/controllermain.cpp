#include "controllermain.h"

ControllerMain::ControllerMain() : AbstractController(), m_libraries() {
	engine().addImportPath(QStringLiteral(QML_IMPORT_PATH));
	qDebug() << QStringLiteral(QML_IMPORT_PATH) << "Wesh"
					 << engine().importPathList();
}

void ControllerMain::exec() {
	qDebug() << "DataXml" << qRegisterMetaType<DataXml>();
	qDebug() << "DataJson" << qRegisterMetaType<DataJson>();
	qDebug() << "MediaPlayer::MediaRole"
					 << qRegisterMetaType<MediaPlayerGlobal::MediaRole>();

	qDebug() << "LibraryProbe"
					 << qmlRegisterUncreatableType<LibraryProbe>(
									"MediaPlayer", 1, 0, "LibraryProbe", "Cpp owner");
	qDebug() << "Library"
					 << qmlRegisterUncreatableType<Library>("MediaPlayer", 1, 0,
																									"Library", "Cpp owner");

	qDebug() << "LibraryDataModel"
					 << qmlRegisterType<LibraryDataModel>("MediaPlayer.Model", 1, 0,
																								"LibraryDataModel");
	qDebug() << "MediaRole QML"
					 << qmlRegisterUncreatableMetaObject(
									MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
									"MediaPlayer",

									"Media Player global");

	setDb("DataJson");
	auto *context = engine().rootContext();
	context->setContextProperty("_main", this);
	context->setContextProperty("_db", db());
	m_libraries = new ControllerLibrary;
	m_libraries->exec();
	m_engine->createWindow(QUrl("/Main.qml"));
}

QQmlApplicationEngine &ControllerMain::engine() {
	return m_engine->qmlEngine();
}
