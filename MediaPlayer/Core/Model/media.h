#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QDateTime>
#include <QCryptographicHash>
#include <QFile>
#include <QMap>
#include <QSharedPointer>
#include "global.h"

class Media;

typedef QSharedPointer<Media> MediaPointer;

class Media
{
private:
    MD5 m_id;    
    MediaPlayerGlobal::MediaRole m_role;
    QString m_path;
    int m_count;
    QDate m_added;
    QDateTime m_lastFinish;
    double m_currentRead;
    
    
public:
    Media();
    Media(const Media& other) = default;
    ~Media() = default;
    
    Media& operator= (const Media& other);
    
    MD5 id() const;
    void setId(MD5 id);
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole role);
    QString path() const;
    void setPath(QString path);
    int count() const;
    void setCount(int count);
    QDate added() const;
    void setAdded(QDate added);
    QDateTime lastFinish() const;
    void setLastFinish(QDateTime lastFinish);
    double currentRead() const;
    void setCurrentRead(double currentRead);
    
    static MediaPointer createMedia(QString path);
};


#endif // MEDIA_H
