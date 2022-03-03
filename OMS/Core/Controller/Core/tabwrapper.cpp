#include "tabwrapper.h"

#include <Controller/DataModel/librarydatamodel.h>

Q_LOGGING_CATEGORY(tabwrapperlog, "tabwrapper.log")

TabWrapper::TabWrapper(LiveQmlEngine& engine): m_engine(engine) {}

QUuid TabWrapper::create()
{
    auto manager = new TabManager;
    m_model[manager->id()] = manager;

    connect(manager, &TabManager::clicked, this, &TabWrapper::setCurrentTab);

    return manager->id();
}

QPointer<TabManager> TabWrapper::get(QUuid id)
{
    return m_model.contains(id) ? m_model[id] : nullptr;
}

QPointer<TabManager> TabWrapper::get(QString id)
{
    return get(QUuid::fromString(id));
}

void TabWrapper::setCurrentTab(QString id)
{
    m_current = QUuid::fromString(id);
    emit currentTabChanged();
}

TabManager* TabWrapper::current()
{
    auto it = std::find_if(m_model.begin(), m_model.end(), [this](const QPointer<TabManager>& tab) {
        return tab->contains(m_current);
    });

    return it == m_model.end() ? nullptr : *it;
}

void TabWrapper::setPlayer(int lib, QObject *p)
{
    auto tab = current();
    (*tab)[m_current].player = p;
    (*tab)[m_current].libIndex = lib;
    auto index = tab->indexOf(m_current);
    auto modelIndex = tab->index(index, 0);

    emit tab->dataChanged(modelIndex, modelIndex, {int(TabManager::TabRole::PlayerRole), int(TabManager::TabRole::LibraryIndex)});
}

void TabWrapper::setPlaylist(int pli)
{
    auto tab = current();
    (*tab)[m_current].playlistIndex = pli;
    auto index = tab->indexOf(m_current);
    auto modelIndex = tab->index(index, 0);
    emit tab->dataChanged(modelIndex, modelIndex, {int(TabManager::TabRole::PLaylistIndex)});
}

QUuid TabWrapper::currentId() const
{
    return m_current;
}

bool TabWrapper::removeManager(QString id)
{
    if(m_model.count() == 1) {
        return false;
    }

    auto count = m_model.remove(QUuid::fromString(id)) > 0;
    return count > 0;
}

void TabWrapper::createWindow()
{
    auto id = QUuid::createUuid();
    m_libraries[id] = new LibraryDataModel;
    QJSEngine::setObjectOwnership(m_libraries[id].data(), QJSEngine::CppOwnership);
    auto root = m_engine.qmlEngine().rootContext();
    auto db = root->contextProperty("_db").value<InterfaceSaver*>();
    connect(db, &InterfaceSaver::librariesChanged, m_libraries[id], &LibraryDataModel::onUpdateLibraries);
    emit db->librariesChanged();
    auto *context = new QQmlContext(root);
    context->setContextProperty("_librariesModel", m_libraries[id].data());
    m_engine.createWindow(QUrl("SubWindow.qml"), context);

    connect(m_libraries[id], &LibraryDataModel::currentIndexChanged, [id, this]() {
        auto index = m_libraries[id]->currentIndex();
        auto cl = m_libraries[id]->controller(index);
        if(cl) {
            auto current = currentId();
            cl->setPlaylistIndex(current.toString(), 0);
            setPlayer(index, cl->playerComp(current.toString()));
        }
    });

}
