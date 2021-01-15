#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary() {
	auto *context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_libraries", this);
	context->setContextProperty("_librariesModel", &m_librariesModel);
	context->setContextProperty("_playlistModel", &m_playlistModel);

	connect(&m_librariesModel, &LibraryDataModel::currentModelChanged, this,
					&ControllerLibrary::onCurrentModelChanged, Qt::UniqueConnection);
}

ControllerLibrary::ControllerLibrary(const ControllerLibrary &)
		: AbstractController() {}

void ControllerLibrary::exec() {}

Library *ControllerLibrary::currentLibrary() const {
	return m_currentLibrary.data();
}

void ControllerLibrary::setCurrentLibrary(QString l) {
	auto lib = db()->selectLibrary()[QUuid::fromString(l)];

	m_currentLibrary = lib;

	emit currentLibraryChanged();
}

void ControllerLibrary::open() {
	m_engine->createWindow(QUrl(QStringLiteral("/LibraryView.qml")));
}

void ControllerLibrary::addSourceDir(QString source) {
	m_currentLibrary->addSourceDir(source);
	db()->updateLibrary(m_currentLibrary);
}

void ControllerLibrary::removeSourceDir(QString path) {
	m_currentLibrary->removeSourceDir(path);
	db()->updateLibrary(m_currentLibrary);
}

void ControllerLibrary::onCurrentModelChanged(LibraryPointer p) {
	m_currentLibrary = p;

	connect(m_currentLibrary.data(), &Library::mediasChanged, this,
					&ControllerLibrary::onMediaChanged, Qt::UniqueConnection);
	emit currentLibraryChanged();

	m_playlistModel.setSmart(m_currentLibrary->smartPlaylist().values());
	m_playlistModel.setNormal(m_currentLibrary->playlist().values());
}

void ControllerLibrary::onMediaChanged() {
	qDebug() << "Prout";
	db()->updateLibrary(m_currentLibrary);
}
