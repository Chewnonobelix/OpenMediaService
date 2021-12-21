#pragma once

#include <QImage>
#include <QTemporaryDir>
#include <QDomDocument>
#include <QDomElement>

#include <Model/media.h>

class ComicsMedia: public QObject
{
    Q_OBJECT

private:
    QSharedPointer<QTemporaryDir> m_extractDir;
    MediaPointer m_base;
    bool m_isLoad = false;

public:
    enum class Frequencies {Unknow, Annual, Monthly, OneShot, TwiceMonthly, Weekly};
    Q_ENUM(Frequencies)
    enum class Forms{Unknow, ComicBook, GraphicNovel, Omnibus, TradePaperback, WebComic};
    Q_ENUM(Forms)
    enum class Formats{Unknow, Print, Digital};
    Q_ENUM(Formats)

    ComicsMedia() = default;
    ComicsMedia(const ComicsMedia&);
    ComicsMedia(MediaPointer);
    ~ComicsMedia() = default;
    ComicsMedia& operator =(const ComicsMedia&);

    QString cover() const;
    void initComicsInfo();

    QSharedPointer<QTemporaryDir> dir() const;
    MediaPointer base() const;

    void load();
    void unload();

    bool isLoad() const;

    bool addPageTag(QString, QString);
    bool removePageTag(QString, QString);
    QStringList pageTag(QString) const;

public:
    QString country() const;
    QDate coverDate() const;
    QString coverPrice() const;
    QString imprintName() const;
    Frequencies indicialFrequency() const;
    QString issueNumber() const;
    QString language() const;
    QString number() const;
    QDate onSaleDate() const;
    QString price() const;
    int printing() const;
    QDate publicationDate() const;
    Frequencies publicationFrequency() const;
    QString publisherName() const;
    QString seriesTitle() const;
    QString title() const;
    QString variance() const;
    QString volumeNumber() const;
};

