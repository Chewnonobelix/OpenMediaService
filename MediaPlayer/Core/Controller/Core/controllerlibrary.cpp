#include "controllerlibrary.h"

QMap<ControllerLibrary *, bool> ControllerLibrary::m_actives =
		QMap<ControllerLibrary *, bool>();

ControllerLibrary::ControllerLibrary() {
	auto *context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_libraries", this);
	m_actives[this] = isActive();
}

ControllerLibrary::ControllerLibrary(const ControllerLibrary &)
		: AbstractController() {
	m_actives[this] = isActive();
}

ControllerLibrary::~ControllerLibrary() { m_actives.remove(this); }

void ControllerLibrary::exec() {}

Library *ControllerLibrary::currentLibrary() const {
	return m_currentLibrary.data();
}

void ControllerLibrary::open() {
	m_engine->createWindow(QUrl(QStringLiteral("/LibraryView.qml")));
}

void ControllerLibrary::addSourceDir(QString source) {
	m_currentLibrary->addSourceDir(source);
}

void ControllerLibrary::removeSourceDir(QString path) {
	m_currentLibrary->removeSourceDir(path);
}

void ControllerLibrary::onCurrentModelChanged(LibraryPointer p) {
	m_currentLibrary = p;

	if (p) {
		connect(p.data(), &Library::libraryChanged, this,
						&ControllerLibrary::onLibraryChanged);

		emit currentLibraryChanged();

		p->probe()->setFilters(m_manager[p->role()]->filters());
	}
}
void ControllerLibrary::onCurrentPlaylistChanged(PlaylistPointer p) {
	//	auto p = m_playlistModel.current();
	if (m_currentLibrary && !p.isNull() && m_manager[m_currentLibrary->role()])
		m_manager[m_currentLibrary->role()]->setPlaylist(p);
}

void ControllerLibrary::addPlaylist(bool smart) {
	if (smart) {
		auto pl = factory<SmartPlaylist>();
		m_currentLibrary->addSmartPlaylist(pl);
	} else {
		auto pl = factory<PlayList>();
		m_currentLibrary->addPlaylist(pl);
	}
}

void ControllerLibrary::removePlaylist(QString id) {
	m_currentLibrary->removePlaylist(id);
	m_currentLibrary->removeSmartPlaylist(id);
}

void ControllerLibrary::onLibraryChanged() {
	db()->updateLibrary(m_currentLibrary);
}

int ControllerLibrary::modelIndex() const { return m_modelIndex; }

void ControllerLibrary::setModelIndex(int i) {
	m_modelIndex = i;
	emit modelIndexChanged();
}

void ControllerLibrary::setCurrentLibrary(QString id) {
	qDebug() << "Set" << m_actives.key(true) << id << this;
	auto p = (*m_librariesModel)[QUuid::fromString(id)];
	m_actives.key(true)->onCurrentModelChanged(p);
}

bool ControllerLibrary::isActive() const { return m_isActive; }

void ControllerLibrary::setActive(bool a) {
	m_isActive = a;
	emit isActiveChanged();

	if (a) {
		for (auto it : m_actives.keys())
			m_actives[it] = false;

		m_actives[this] = a;
	}
}
