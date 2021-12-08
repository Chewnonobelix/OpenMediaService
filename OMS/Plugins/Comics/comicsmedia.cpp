#include "comicsmedia.h"

#include <xml2json.hpp>

ComicsMedia::ComicsMedia(const ComicsMedia& cm): QObject(), m_extractDir(cm.dir()), m_base(cm.base())
{}

ComicsMedia::ComicsMedia(MediaPointer media): m_base(media)
{
}

ComicsMedia& ComicsMedia::operator =(const ComicsMedia& cm)
{
    m_base = cm.base();
    m_extractDir = cm.dir();
    return *this;
}

QString ComicsMedia::cover() const
{
    QDir dir;
    dir.cd("cache");

    auto list = dir.entryInfoList({QString("%1.*").arg(m_base->id().toString())});
    QString ret;
    if(list.isEmpty()) {
        QProcess uz;
        uz.setProgram("3rdParty/7z");
        uz.setArguments({"l", m_base->path()});
        uz.start();
        uz.waitForFinished();
        auto lines = QString(uz.readAllStandardOutput()).split('\n');
        auto first = lines[lines.indexOf(QRegularExpression(".*jpg.*"))];
        auto fileName = first.split(' ').last().remove('\r');

        uz.setArguments({"e", QString("-i!%1").arg(fileName), m_base->path(), "-otemp/*"});
        uz.start();
        uz.waitForFinished();
        QFileInfo info(m_base->path());
        auto base = info.baseName();
        QFile file(QString("temp/%1/%2").arg(base).arg(fileName));
        ret = QString("cache/%1.%2").arg(m_base->id().toString()).arg(fileName.split('.').last());
        file.copy(ret);
    }
    else
    {
        ret = list[0].absoluteFilePath();
    }

//    return QImage(ret);
    return ret;
}

QSharedPointer<QTemporaryDir> ComicsMedia::dir() const
{
    return m_extractDir;
}

void ComicsMedia::load()
{
    auto p = m_base->path().split("/").last().split(".").first();
    m_extractDir = factory<QTemporaryDir>("temp/"+p);

    m_extractDir->setAutoRemove(false);
    QProcess uz;

    uz.setProgram("3rdParty/7z");
    uz.setArguments(QStringList()<<"x"<<"-o"+m_extractDir->path()<<m_base->path());
    uz.start();
    uz.waitForFinished();

    QDir dir;
    dir.cd(m_extractDir->path());
    dir.mkdir("split");

    auto list = dir.entryInfoList({"*.jpg"});

    for(auto it: list) {
        QImage i(it.absoluteFilePath());

        if(i.width() > i.height()) {
            auto t1 = i.copy(0,0, i.width() / 2, i.height());
            auto t2 = i.copy(i.width() / 2,0, i.width() / 2, i.height());
            t1.save(m_extractDir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1));
            t2.save(m_extractDir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2));
        }
    }

    m_isLoad = m_extractDir && !list.isEmpty();
}

void ComicsMedia::unload()
{
    m_extractDir.clear();
    m_isLoad = false;
}

MediaPointer ComicsMedia::base() const
{
    return m_base;
}

void ComicsMedia::initComicsInfo()
{
    QProcess uz;
    uz.setProgram("3rdParty/7z");
    uz.setArguments({"l", m_base->path()});
    uz.start();
    uz.waitForFinished();
    auto lines = QString(uz.readAllStandardOutput()).split('\n');
    if(lines.indexOf(QRegularExpression(".*xml.*")) == -1)
        return;

    auto first = lines[lines.indexOf(QRegularExpression(".*xml.*"))];
    auto fileName = first.split(' ').last().remove('\r');

    uz.setArguments({"e", QString("-i!%1").arg(fileName), m_base->path(), "-otemp/*"});
    uz.start();
    uz.waitForFinished();
    QFileInfo info(m_base->path());
    auto base = info.baseName();

    QFile file(QString("temp/%1/%2").arg(base).arg(fileName));
    if(!file.open(QIODevice::ReadOnly))
        return;

    auto jsonstring = xml2json(file.readAll());
    qDebug()<<jsonstring.c_str();
    auto filler = [this](auto json) {

    };
    auto json = QJsonDocument::fromJson(jsonstring.c_str());
}

bool ComicsMedia::isLoad() const
{
    return m_isLoad;
}

QString ComicsMedia::country() const
{
    return QString();
}

QDate ComicsMedia::coverDate() const
{
    return QDate();
}

QString ComicsMedia::coverPrice() const
{
    return QString();
}

QString ComicsMedia::imprintName() const
{
    return QString();
}

ComicsMedia::Frequencies ComicsMedia::indicialFrequency() const
{
    return Frequencies::Unknow;
}

QString ComicsMedia::issueNumber() const
{
    return QString();
}

QString ComicsMedia::language() const
{
    return QString();
}

QString ComicsMedia::number() const
{
    return QString();
}

QDate ComicsMedia::onSaleDate() const
{
    return QDate();
}

QString ComicsMedia::price() const
{
    return QString();
}

int ComicsMedia::printing() const
{
    return 0;
}

QDate ComicsMedia::publicationDate() const
{
    return QDate();
}

ComicsMedia::Frequencies ComicsMedia::publicationFrequency() const
{
    return Frequencies::Unknow;
}

QString ComicsMedia::publisherName() const
{
    return QString();
}

QString ComicsMedia::seriesTitle() const
{
    return QString();
}

QString ComicsMedia::title() const
{
    return QString();
}

QString ComicsMedia::variance() const
{
    return QString();
}

QString ComicsMedia::volumeNumber() const
{
    return QString();
}

