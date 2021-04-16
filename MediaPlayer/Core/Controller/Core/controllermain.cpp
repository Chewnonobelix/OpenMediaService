#include "controllermain.h"

ControllerMain::ControllerMain() : AbstractController() {
	engine().addImportPath(QStringLiteral(QML_IMPORT_PATH));
    qDebug() << QStringLiteral(QML_IMPORT_PATH)
					 << engine().importPathList();
	m_manager.init();
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
	qDebug() << "ControllerLibrary"
					 << qmlRegisterType<ControllerLibrary>("MediaPlayer.Model", 1, 0,
																								 "ControllerLibrary");
	qDebug() << "MediaRole QML"
					 << qmlRegisterUncreatableMetaObject(
									MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
									"MediaPlayer",

									"Media Player global");
	qDebug() << "InterfacePLugin"
					 << qmlRegisterUncreatableType<InterfacePlugins>(
									"InterfacePlugin", 1, 0, "InterfacePlugin", "Interface type");

	qDebug() << qmlRegisterType<TabManager>("MediaPlayer.Model", 1, 0,
																					"MediaPlayer");

	setDb("DataJson");
	auto *context = engine().rootContext();
	context->setContextProperty("_main", this);
	context->setContextProperty("_db", db());
	m_librariesModel = new LibraryDataModel;

	context->setContextProperty("_librariesModel", m_librariesModel);

	qDebug() << "Main context";

	connect(db(), &InterfaceSaver::librariesChanged, m_librariesModel,
					&LibraryDataModel::onUpdateLibraries);

	m_engine->createWindow(QUrl("/Main.qml"));

	emit db()->librariesChanged();
}

QQmlApplicationEngine &ControllerMain::engine() {
	return m_engine->qmlEngine();
}

