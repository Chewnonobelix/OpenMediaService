#ifndef SMARTPLAYLIST_H
#define SMARTPLAYLIST_H

#include "playlist.h"

class SmartPlaylist: public PlayList
{
    Q_OBJECT
    
private:
    QVariantMap m_critera;
    
public:
    SmartPlaylist() = default;
    SmartPlaylist(const SmartPlaylist&) = default;
    ~SmartPlaylist() = default;
    
    void setCritera(QString, QVariant);
    bool removeCritera(QString);
    QVariantMap critera() const;
   
public slots:
    void update(MediaPointer);
};

#endif // SMARTPLAYLIST_H
