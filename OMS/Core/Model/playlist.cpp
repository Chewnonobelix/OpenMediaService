#include "playlist.h"

PlayList::PlayList(const PlayList &p)
        : QObject(nullptr), MetaData(p), QEnableSharedFromThis<PlayList>(), QList(p) {}

PlayList &PlayList::operator=(const PlayList &p) {
	MetaData &m = *this;
	m = p;
	QList<MediaPointer> &m2 = *this;
	m2 = p;

	return *this;
}

PlayList::PlayList(const QJsonObject& json): QObject(nullptr), MetaData(json), QEnableSharedFromThis<PlayList>(),
    QList()
{
    auto array = json["medias"].toArray();

    for(auto it: array) {
        append(factory<Media>(QUuid::fromString(it.toString())));
    }
}


PlayList::operator QJsonObject() const
{
    QJsonObject ret = MetaData::operator QJsonObject();

    QJsonArray array;

    for(auto it: *this) {
        array<<it->id().toString();
    }

    ret["medias"] = array;

    return ret;
}

QUuid PlayList::id() const { return metaData<QUuid>("id"); }

bool PlayList::setId(QUuid id) { return setMetadata("id", id); }

QString PlayList::name() const { return metaData<QString>("name"); }

bool PlayList::setName(QString name) {
    auto ret = setMetadata("name", name);
	emit nameChanged();
    return ret;
}

bool PlayList::isShuffle() const { return metaData<bool>("isShuffle"); }

bool PlayList::setShuffle(bool s) {
    auto ret = setMetadata("isShuffle", s);
	emit isShuffleChanged();
    return ret;
}

QFuture<bool> PlayList::append(MediaPointer m, int index) {
    //TODO
    if (index == -1)
		QList<MediaPointer>::append(m);
	else
		insert(index, m);

	emit countChanged();
    return QtConcurrent::run([]() {return true;});
}

bool PlayList::append(Media* m, int index)
{
    return append(m->sharedFromThis(), index).result();
}

bool PlayList::remove(int index) {
    //TODO
    removeAt(index);

	emit countChanged();
    return true;
}

MediaPointer PlayList::at(int i) const { return (*this)[i]; }

bool PlayList::swap(int i, int j) {
    //TODO
	swapItemsAt(i, j);

	emit countChanged();
    return true;
}

bool PlayList::clear() {
	QList<MediaPointer>::clear();
	emit countChanged();
    return isEmpty();
}

MediaPointer PlayList::next() {
	MediaPointer ret;

    if (!m_readOrder.isEmpty()) {
        auto index = m_readOrder.takeFirst();
		ret = at(index);
        emit play(ret);
    }
	return ret;
}

MediaPointer PlayList::prev() {
	MediaPointer ret;

    if (currentIndex() > 0) {
		setCurrentIndex(currentIndex() - 1);
		auto index = m_readOrder[currentIndex()];
		ret = at(index);
        emit play(ret);
	}

	return ret;
}

bool PlayList::setReadOrder(QList<int> order) {
    if(m_readOrder == order)
        return false;

    m_readOrder = order;
    return true;
}

int PlayList::currentIndex() const { return m_currentIndex; }

bool PlayList::setCurrentIndex(int index) {
    if(m_currentIndex == index)
        return false;

    m_currentIndex = index;
	emit currentIndexChanged();
    return true;
}

void PlayList::set()
{
    connect(this, &PlayList::nameChanged, this, &PlayList::playlistChanged);
    connect(this, &PlayList::countChanged, this, &PlayList::playlistChanged);
    connect(this, &PlayList::isShuffleChanged, this, &PlayList::playlistChanged);
}

bool PlayList::contains(QUuid id) const
{
    return std::find_if(begin(), end(), [id](MediaPointer m) {
        return m->id() == id;
    }) != end();
}

bool PlayList::replace(MediaPointer m)
{
    auto ret = contains(m->id());

    if(ret) {
        (*this)[indexOf(m->id())] = m;
    }

    return ret;
}

int PlayList::indexOf(QUuid id) const
{
    auto it = std::find_if(begin(), end(), [id](MediaPointer m) {
            return m->id() == id;
    });
    return std::distance(begin(), it);
}

QList<int> PlayList::readOrder() const
{
    return m_readOrder;
}
