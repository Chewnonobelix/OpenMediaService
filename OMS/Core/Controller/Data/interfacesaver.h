#pragma once

#include <QObject>

#include "../../Model/library.h"

class MEDIAPLAYERCORE_EXPORT InterfaceSaver : public QObject {

	Q_OBJECT

private:
public:
	InterfaceSaver() = default;
	InterfaceSaver(const InterfaceSaver &);
	virtual ~InterfaceSaver() = default;

	virtual void init() = 0;

public slots:
	virtual QMap<QUuid, LibraryPointer> selectLibrary() const = 0;
	virtual bool createLibrary(QString, MediaPlayerGlobal::MediaRole) = 0;
	virtual bool removeLibrary(QString) = 0;
	virtual bool updateLibrary(LibraryPointer) = 0;

protected slots:
    virtual bool insertMedia(MediaPointer);
    virtual bool deleteMedia(QUuid);
    virtual bool updateMedia(QUuid);

    virtual bool insertPlaylist(PlaylistPointer);
    virtual bool deletePlaylist(QUuid);
    virtual bool updatePlaylist(QUuid);

    virtual bool insertSmartGroup(SmartGroupPointer);
    virtual bool deleteSmartGroup(QUuid);
    virtual bool updateSmartGroup(QUuid);

    virtual bool insertSmartRule(SmartRulePointer);
    virtual bool deleteSmartRule(QUuid);
    virtual bool updateSmartRule(QUuid);

signals:
	void librariesChanged();
};
