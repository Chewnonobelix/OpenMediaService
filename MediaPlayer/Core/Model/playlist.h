#pragma once

#include <QList>
#include <QSharedPointer>
#include <QUuid>
#include <QVariant>

#include "global.h"
#include "media.h"

class PlayList;

typedef QSharedPointer<PlayList> PlaylistPointer;

class PlayList : public QObject, public MetaData, private QList<MediaPointer> {
	Q_OBJECT

	Q_PROPERTY(QUuid id READ id CONSTANT)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(int count READ count NOTIFY countChanged)

private:
public:
	PlayList() = default;
	using MetaData::MetaData;
	PlayList(const PlayList &);
	~PlayList() = default;

	PlayList &operator=(const PlayList &);

	using QList<MediaPointer>::count;
	using QList<MediaPointer>::isEmpty;
	using QList<MediaPointer>::operator[];

	QUuid id() const;
	void setId(QUuid);
	QString name() const;
	void setName(QString);

signals:
	void nameChanged(QString);
	void countChanged();

public slots:
	Q_INVOKABLE virtual void append(MediaPointer, int = -1);
	Q_INVOKABLE void remove(int);
	Q_INVOKABLE MediaPointer at(int i) const;
	Q_INVOKABLE void swap(int, int);
	Q_INVOKABLE void clear();
};
