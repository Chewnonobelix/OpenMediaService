#include "playlist.h"

PlayList::PlayList(const PlayList &p)
		: QObject(nullptr), MetaData(p), QList(p) {}

PlayList &PlayList::operator=(const PlayList &p) {
	MetaData &m = *this;
	m = p;
	QList<MediaPointer> &m2 = *this;
	m2 = p;

	return *this;
}

QUuid PlayList::id() const { return metaData<QUuid>("id"); }

void PlayList::setId(QUuid id) { setMetadata("id", id); }

QString PlayList::name() const { return metaData<QString>("name"); }

void PlayList::setName(QString name) {
	setMetadata("name", name);
	emit nameChanged();
}

bool PlayList::isShuffle() const { return metaData<bool>("isShuffle"); }

void PlayList::setShuffle(bool s) {
	setMetadata("isShuffle", s);
	emit isShuffleChanged();
}

void PlayList::append(MediaPointer m, int index) {
	if (index == -1)
		QList<MediaPointer>::append(m);
	else
		insert(index, m);

	emit countChanged();
}

void PlayList::remove(int index) {
	removeAt(index);

	emit countChanged();
}

MediaPointer PlayList::at(int i) const { return (*this)[i]; }

void PlayList::swap(int i, int j) {
	swapItemsAt(i, j);

	emit countChanged();
}

void PlayList::clear() {
	QList<MediaPointer>::clear();
	emit countChanged();
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

void PlayList::setReadOrder(QList<int> order) { m_readOrder = order; }

int PlayList::currentIndex() const { return m_currentIndex; }

void PlayList::setCurrentIndex(int index) {
	m_currentIndex = index;
	emit currentIndexChanged();
}

void PlayList::set()
{
    connect(this, &PlayList::nameChanged, this, &PlayList::playlistChanged);
    connect(this, &PlayList::countChanged, this, &PlayList::playlistChanged);
    connect(this, &PlayList::isShuffleChanged, this, &PlayList::playlistChanged);
}
