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


public:
    enum class Frequencies {Annual, Monthly, OneShot, TwiceMonthly, Weekly};
    Q_ENUM(Frequencies)
    enum class Forms{ComicBook, GraphicNovel, Omnibus, TradePaperback, WebComic};
    Q_ENUM(Forms)
    enum class Formats{Print, Digital};
    Q_ENUM(Formats)

    ComicsMedia() = default;
    ComicsMedia(MediaPointer);

    QString cover() const;
    void initComicsInfo();

    QSharedPointer<QTemporaryDir> dir() const;
    MediaPointer base() const;

    void load();
    void unload();


};

