#include "controllermain.h"

ControllerMain::ControllerMain() : AbstractController(), m_libraries() {
	engine().addImportPath(QStringLiteral(QML_IMPORT_PATH));
	qDebug() << QStringLiteral(QML_IMPORT_PATH) << "Wesh"
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
	qDebug() << "ControllerLibrairy"
					 << qmlRegisterType<ControllerLibrary>("MediaPlayer.Model", 1, 0,
																								 "ControllerLibrairy");
	qDebug() << "MediaRole QML"
					 << qmlRegisterUncreatableMetaObject(
									MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
									"MediaPlayer",

									"Media Player global");

	setDb("DataJson");
	auto *context = engine().rootContext();
	context->setContextProperty("_main", this);
	context->setContextProperty("_db", db());
	m_libraries << new ControllerLibrary;
	m_libraries.first()->exec();

	connect(m_libraries.first(), &ControllerLibrary::currentLibraryChanged, this,
					&ControllerMain::onLibraryChanged);

	m_engine->createWindow(QUrl("/Main.qml"));
}

QQmlApplicationEngine &ControllerMain::engine() {
	return m_engine->qmlEngine();
}

void ControllerMain::onLibraryChanged() {
	auto role = m_libraries.first()->currentLibrary()->role();
	if (m_manager[role]) {
		emit playlistDisplay(m_manager[role]->playlistView());
		emit playerDisplay(m_manager[role]->playerView());
	} else {
		emit playlistDisplay("");
		emit playerDisplay("");
	}
}

void ControllerMain::addSplit(int i, int) {
	QPointer<ControllerLibrary> t = new ControllerLibrary;
	m_libraries.resize(m_libraries.size() + 1);
	m_libraries.insert(i, t);
}

void ControllerMain::removeSplit(int i, int) { m_libraries.removeAt(i); }
