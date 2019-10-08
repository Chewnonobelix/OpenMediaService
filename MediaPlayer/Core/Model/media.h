#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QDateTime>
#include <QCryptographicHash>
#include <QFile>
#include <QMap>
#include <QSharedPointer>
#include <QSet>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include "global.h"
#include "metadata.h"

class Media;

typedef QSharedPointer<Media> MediaPointer;

class Media: public Metadata
{
    Q_GADGET
    
    Q_PROPERTY(MD5 id READ id)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role)
    Q_PROPERTY(bool isAvailable READ isAvailable)
    Q_PROPERTY(QDate added READ added)
    Q_PROPERTY(QDateTime lastFinish READ lastFinish)
    Q_PROPERTY(double currentRead READ currentRead WRITE setCurrentRead)
    Q_PROPERTY(QStringList paths READ paths)
    
private:
    QSet<QString> m_path;
    
    
public:
    Media(MD5 = "", QString = "");
    Media(const Media& other) = default;
    ~Media() = default;
    
    Media& operator= (const Media& other);
    
    MD5 id() const;
    void setId(MD5 id);
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole role);
    QString path() const;
    QList<QString> paths() const;
    void setPath(QString path);
    int nbPath() const;
    bool isAvailable() const;
    int count() const;
    void setCount(int count);
    QDate added() const;
    void setAdded(QDate added);
    QDateTime lastFinish() const;
    void setLastFinish(QDateTime lastFinish);
    double currentRead() const;
    void setCurrentRead(double currentRead);
    
    
    friend MediaPointer operator << (MediaPointer, QString);
    void operator ++(int);
    Q_INVOKABLE bool pp();
    static MediaPointer createMedia(MD5, QString path = "");
};

Q_DECLARE_METATYPE(Media)
#endif // MEDIA_H
