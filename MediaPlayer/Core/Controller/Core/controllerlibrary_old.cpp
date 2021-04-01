#include "controllerlibrary_old.h"

QMap<ControllerLibrary_old *, bool> ControllerLibrary_old::m_actives =
		QMap<ControllerLibrary_old *, bool>();

ControllerLibrary_old::ControllerLibrary_old() {
	auto *context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_libraries", this);
	m_actives[this] = isActive();
}

ControllerLibrary_old::ControllerLibrary_old(const ControllerLibrary_old &)
		: AbstractController() {
	m_actives[this] = isActive();
}

ControllerLibrary_old::~ControllerLibrary_old() { m_actives.remove(this); }

void ControllerLibrary_old::exec() {}

Library *ControllerLibrary_old::currentLibrary() const {
	return m_currentLibrary.data();
}

void ControllerLibrary_old::open() {
	m_engine->createWindow(QUrl(QStringLiteral("/LibraryView.qml")));
}

void ControllerLibrary_old::addSourceDir(QString source) {
	m_currentLibrary->addSourceDir(source);
}

void ControllerLibrary_old::removeSourceDir(QString path) {
	m_currentLibrary->removeSourceDir(path);
}

void ControllerLibrary_old::onCurrentModelChanged(LibraryPointer p) {
	m_currentLibrary = p;

	if (p) {
		connect(p.data(), &Library::libraryChanged, this,
						&ControllerLibrary_old::onLibraryChanged);

		emit currentLibraryChanged();

		p->probe()->setFilters(m_manager[p->role()]->filters());
		m_plugins = m_manager[p->role()]->clone();
		m_plugins->exec();
		qDebug() << "Fils de pute" << p;
		m_playlist.onLibraryChanged(p);
	}
}
void ControllerLibrary_old::onCurrentPlaylistChanged(PlaylistPointer p) {
	//		auto p = m_playlistModel.current();
	if (m_currentLibrary && !p.isNull() && m_manager[m_currentLibrary->role()])
		m_manager[m_currentLibrary->role()]->setPlaylist(p);
}

void ControllerLibrary_old::addPlaylist(bool smart) {
	if (smart) {
		auto pl = factory<SmartPlaylist>();
		m_currentLibrary->addSmartPlaylist(pl);
	} else {
		auto pl = factory<PlayList>();
		m_currentLibrary->addPlaylist(pl);
	}
}

void ControllerLibrary_old::removePlaylist(QString id) {
	m_currentLibrary->removePlaylist(id);
	m_currentLibrary->removeSmartPlaylist(id);
}

void ControllerLibrary_old::onLibraryChanged() {
	db()->updateLibrary(m_currentLibrary);
}

int ControllerLibrary_old::modelIndex() const { return m_modelIndex; }

void ControllerLibrary_old::setModelIndex(int i) {
	m_modelIndex = i;
	emit modelIndexChanged();
}

void ControllerLibrary_old::setCurrentLibrary(QString id) {
	auto p = (*m_librariesModel)[QUuid::fromString(id)];
	m_actives.key(true)->onCurrentModelChanged(p);
}

bool ControllerLibrary_old::isActive() const { return m_isActive; }

void ControllerLibrary_old::setActive(bool a) {
	m_isActive = a;
	emit isActiveChanged();

	if (a) {
		for (auto it : m_actives.keys())
			m_actives[it] = false;

		m_actives[this] = a;

		auto index = m_librariesModel->indexOf(m_currentLibrary);
		m_librariesModel->setCurrentIndex(index);
	}
}

ControllerLibrary_old *ControllerLibrary_old::active() {
	return m_actives.key(true);
}

QSharedPointer<InterfacePlugins> ControllerLibrary_old::plugins() {
	return m_plugins;
}

PlaylistModel *ControllerLibrary_old::playlist() { return &m_playlist; }
