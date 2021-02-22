#include "controllermain.h"

ControllerMain::ControllerMain() : AbstractController() {
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
	qDebug() << "ControllerLibrary"
					 << qmlRegisterType<ControllerLibrary>("MediaPlayer.Model", 1, 0,
																								 "ControllerLibrary");
	qDebug() << "MediaRole QML"
					 << qmlRegisterUncreatableMetaObject(
									MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
									"MediaPlayer",

									"Media Player global");

	setDb("DataJson");
	auto *context = engine().rootContext();
	context->setContextProperty("_main", this);
	context->setContextProperty("_db", db());
	//	m_libraries << new ControllerLibrary;
	//	m_libraries.first()->exec();
	m_librariesModel = new LibraryDataModel;
	m_playlistModel = new PlaylistModel;

	context->setContextProperty("_librariesModel", m_librariesModel);
	context->setContextProperty("_playlistModel", m_playlistModel);

	//	connect(m_librariesModel, &LibraryDataModel::currentModelChanged,
	//					[this](LibraryPointer l) {
	//						m_libraries[m_currentTab]->onCurrentModelChanged(l);
	//						m_libraries[m_currentTab]->setModelIndex(
	//								m_librariesModel->currentIndex());
	//					});

	//	connect(m_playlistModel, &PlaylistModel::currentIndexChanged,
	//					[this](PlaylistPointer p) {
	//						m_libraries[m_currentTab]->onCurrentPlaylistChanged(p);
	//					});

	connect(db(), &InterfaceSaver::librariesChanged, m_librariesModel,
					&LibraryDataModel::onUpdateLibraries);

	connect(m_librariesModel, &LibraryDataModel::currentModelChanged,
					m_playlistModel, &PlaylistModel::onLibraryChanged);

	//	connect(m_libraries.first(), &ControllerLibrary::currentLibraryChanged,
	// this, &ControllerMain::onLibraryChanged);

	m_engine->createWindow(QUrl("/Main.qml"));

	emit db()->librariesChanged();
}

QQmlApplicationEngine &ControllerMain::engine() {
	return m_engine->qmlEngine();
}

void ControllerMain::onLibraryChanged() {
	auto s = (ControllerLibrary *)sender();
	auto role = s->currentLibrary()->role();

	if (m_manager[role]) {
		emit playlistDisplay(m_manager[role]->playlistView());
		emit playerDisplay(m_manager[role]->playerView(), m_currentTab);
	} else {
		emit playlistDisplay("");
		emit playerDisplay("", m_currentTab);
	}
}
