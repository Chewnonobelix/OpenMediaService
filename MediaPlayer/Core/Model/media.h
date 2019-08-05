#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QDateTime>
#include <QCryptographicHash>
#include <QFile>
#include <QMap>
#include <QSharedPointer>
#include <QSet>
#include "global.h"

class Media;

typedef QSharedPointer<Media> MediaPointer;

class Media
{
private:
    MD5 m_id;    
    MediaPlayerGlobal::MediaRole m_role;
    QSet<QString> m_path;
    int m_count;
    QDate m_added;
    QDateTime m_lastFinish;
    double m_currentRead;
    
    
public:
    Media(MD5, QString);
    Media(const Media& other) = default;
    ~Media() = default;
    
    Media& operator= (const Media& other);
    
    MD5 id() const;
    void setId(MD5 id);
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole role);
    QString path() const;
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
    static MediaPointer createMedia(MD5, QString path);
};


#endif // MEDIA_H
