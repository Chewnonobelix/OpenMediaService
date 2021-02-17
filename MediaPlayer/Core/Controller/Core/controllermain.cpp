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
	m_librariesModel = new LibraryDataModel;
	m_playlistModel = new PlaylistModel;

	context->setContextProperty("_librariesModel", m_librariesModel);
	context->setContextProperty("_playlistModel", m_playlistModel);

	connect(m_librariesModel, &LibraryDataModel::currentModelChanged,
					[this](LibraryPointer l) {
						m_libraries[m_currentTab]->onCurrentModelChanged(l);
						m_libraries[m_currentTab]->setModelIndex(
								m_librariesModel->currentIndex());
					});

	connect(m_playlistModel, &PlaylistModel::currentIndexChanged,
					[this](PlaylistPointer p) {
						m_libraries[m_currentTab]->onCurrentPlaylistChanged(p);
					});

	connect(m_librariesModel, &LibraryDataModel::currentModelChanged,
					m_playlistModel, &PlaylistModel::onLibraryChanged);

	connect(m_libraries.first(), &ControllerLibrary::currentLibraryChanged, this,
					&ControllerMain::onLibraryChanged);

	m_engine->createWindow(QUrl("/Main.qml"));
	m_librariesModel->onUpdateLibraries();
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

void ControllerMain::addTab() {
	QPointer<ControllerLibrary> t = new ControllerLibrary;
	m_libraries << (t);
	connect(m_libraries.last(), &ControllerLibrary::currentLibraryChanged, this,
					&ControllerMain::onLibraryChanged);
}

void ControllerMain::onTabChanged(int index) {
	qDebug() << index << m_libraries[index]->modelIndex();
	m_currentTab = index;
	m_librariesModel->setCurrentIndex(m_libraries[index]->modelIndex());
}
