#include "media.h"

Media::Media(MD5 content, QString path) : QObject(nullptr) {
    if (!path.isEmpty())
        m_path << path;

    if(content.isEmpty() && !path.isEmpty())
        initFingerprint();
    else
        setFingerprint(content);

    setCount(0);
    setLastFinish(QDateTime());
    setMetadata("tags", QStringList());
    setMetadata("bookmark", QStringList());
    setRating(0);

    setId(QUuid::createUuid());
    set();
}

Media::Media(QUuid id)
{
    setId(id);

    set();
}
Media::Media(const Media &other)
    : QObject(nullptr), MetaData(other), QEnableSharedFromThis<Media>(),
      m_path(other.paths().begin(), other.paths().end()) {
    set();
}

Media::Media(QJsonObject &obj) : MetaData(obj) {
    auto sources = obj["sources"].toArray();

    for (auto it : sources)
        m_path << it.toString();

    set();
}

Media::operator QJsonObject() const {
    auto ret = MetaData::operator QJsonObject();

    QJsonArray sources;

    for (auto it : m_path)
        sources << it;

    ret["sources"] = sources;
    ret["tags"] = QJsonArray::fromStringList(tags());

    return ret;
}

void Media::set() {
    connect(this, &Media::countChanged, this, &Media::mediaChanged);
    connect(this, &Media::ratingChanged, this, &Media::mediaChanged);
    connect(this, &Media::currentReadChanged, this, &Media::mediaChanged);
    connect(this, &Media::lastFinishChanged, this, &Media::mediaChanged);
    connect(this, &Media::isAvailableChanged, this, &Media::mediaChanged);
    connect(this, &Media::lastProbedChanged, this, &Media::mediaChanged);
    connect(this, &Media::tagsChanged, this, &Media::mediaChanged);
}

QUuid Media::id() const { return metaData<QUuid>("id"); }

bool Media::setId(QUuid id) { return setMetadata("id", id); }

MD5 Media::fingerprint() const
{
    return metaData<MD5>("fingerprint");
}

void Media::setFingerprint(MD5 content)
{
    setMetadata("fingerprint", content);
}

MediaPlayerGlobal::MediaRole Media::role() const {
    return metaData<MediaPlayerGlobal::MediaRole>("role");
}

bool Media::setRole(MediaPlayerGlobal::MediaRole role) {
    return setMetadata("role", role);
}

QString Media::path() const { return *m_path.begin(); }

QList<QString> Media::paths() const { return m_path.values(); }

bool Media::setPath(QString path) {
    if (path.isEmpty() || m_path.contains(path)){
        return false;
    }

    m_path << path;
    emit isAvailableChanged();

    return true;
}

bool Media::removePath(QString path) {
    auto ret = m_path.remove(path);
    emit isAvailableChanged();

    return ret;
}

int Media::count() const {
    return hasMetadata("count") ? metaData<int>("count") : 0;
}

bool Media::setCount(int count) {
    auto ret = setMetadata("count", count);
    emit countChanged();
    return ret;
}

int Media::rating() const {
    return hasMetadata("rating") ? metaData<int>("rating") : 0;
}

bool Media::setRating(int rate) {
    auto ret = setMetadata("rating", rate);
    emit ratingChanged();
    return ret;
}

QDate Media::added() const { return metaData<QDate>("added"); }

bool Media::setAdded(QDate added) { return setMetadata("added", added); }

QDateTime Media::lastFinish() const {
    return metaData<QDateTime>("lastFinish");
}

bool Media::setLastFinish(QDateTime lastFinish) {
    auto ret = setMetadata("lastFinish", lastFinish);
    emit lastFinishChanged();
    return ret;
}

QDateTime Media::lastProbed() const {
    return metaData<QDateTime>("lastProbed");
}

bool Media::setLastProbed(QDateTime lastProbed) {
    auto ret = setMetadata("lastProbed", lastProbed);
    emit lastProbedChanged();
    return ret;
}

double Media::currentRead() const { return metaData<double>("currentRead"); }

bool Media::setCurrentRead(double currentRead) {
    auto ret = setMetadata("currentRead", currentRead);
    emit currentReadChanged();
    return ret;
}

MediaPointer Media::createMedia(MD5 id, QString path) {
    MediaPointer ret = factory<Media>(id, path);
    ret->setAdded(QDate::currentDate());

    return ret;
}

int Media::nbPath() const { return m_path.size(); }

bool Media::isAvailable() const {
    bool ret = !m_path.isEmpty();
    for (auto it = m_path.begin(); ret && it != m_path.end(); it++)
        ret &= QFile::exists(*it);

    return ret;
}

Media &Media::operator=(const Media &other) {

    m_path.clear();
    for (auto it : other.paths())
        m_path << it;

    MetaData &mt = *this;
    mt = other;
    return *this;
}

Media::CompareState compare(MediaPointer m1, MediaPointer m2, QString field)
{
    if(QStringList({"count", "rating", "currenrRead"}).contains(field)) {
        return m1->metaData<double>(field) < m2->metaData<double>(field) ? Media::CompareState::InferiorState : m1->metaData<double>(field) == m2->metaData<double>(field) ? Media::CompareState::EqualState : Media::CompareState::SuperiorState;
    }
    else {
        return m1->metaData<QString>(field) < m2->metaData<QString>(field) ? Media::CompareState::InferiorState : m1->metaData<QString>(field) == m2->metaData<QString>(field) ? Media::CompareState::EqualState : Media::CompareState::SuperiorState;
    }
}

bool Media::hasTag(QString tag) const
{
    return tags().contains(tag);
}

QStringList Media::tags() const
{
    return metaData<QStringList>("tags");
}

void Media::setTags(QStringList tags)
{
    setMetadata("tags", tags);
    emit tagsChanged();
}

void Media::setTag(QString tag)
{
    auto tagss = tags();
    if(hasMetadata(tag))
        tagss.removeAll(tag);
    else
        tagss<<tag;

    setTags(tagss);

    emit tagsChanged();
}

void Media::initFingerprint()
{
    m_runner = QtConcurrent::run([this]() {
        auto p = path();
        QFile file(p);
        if(!file.open(QIODevice::ReadOnly))
            return;

        QCryptographicHash ch(QCryptographicHash::Md5);
        if (!ch.addData(&file))
            return;

        auto md = ch.result();
        setFingerprint(md);
        file.close();
    });
}
