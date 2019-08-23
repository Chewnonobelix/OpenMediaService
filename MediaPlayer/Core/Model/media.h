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
#include "global.h"
#include "metadata.h"

class Media;

typedef QSharedPointer<Media> MediaPointer;

class Media: public Metadata
{
private:
    QSet<QString> m_path;
    
    
public:
    Media(MD5, QString = "");
    Media(const Media& other) = default;
    ~Media() = default;
    
    Media& operator= (const Media& other);
    
    MD5 id() const;
    void setId(MD5 id);
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole role);
    QString path() const;
    QSet<QString> paths() const;
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
    void operator ++();
    static MediaPointer createMedia(MD5, QString path = "");
};


#endif // MEDIA_H
