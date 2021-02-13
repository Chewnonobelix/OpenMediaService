#pragma once

#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QMap>
#include <QObject>
#include <QSet>
#include <QSharedPointer>
#include <QString>
#include <QVariant>

#include <mediaplayercore_global.h>

#include "designpattern.h"
#include "global.h"
#include "metadata.h"

using namespace DesignPattern;

class Media;

typedef QSharedPointer<Media> MediaPointer;

class MEDIAPLAYERCORE_EXPORT Media : public QObject, public MetaData {
	Q_OBJECT

	Q_PROPERTY(MD5 id READ id CONSTANT)
	Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
	Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role CONSTANT)
	Q_PROPERTY(bool isAvailable READ isAvailable NOTIFY isAvailableChanged)
	Q_PROPERTY(QDate added READ added CONSTANT)
	Q_PROPERTY(QDateTime lastFinish READ lastFinish NOTIFY lastFinishChanged)
	Q_PROPERTY(double currentRead READ currentRead WRITE setCurrentRead NOTIFY
								 currentReadChanged)
	Q_PROPERTY(QStringList paths READ paths)
	Q_PROPERTY(int rating READ rating WRITE setRating NOTIFY ratingChanged)

private:
	QSet<QString> m_path;

	void set();

public:
	Media(MD5 = "", QString = "");
	Media(const Media &other);
	using MetaData::MetaData;
	Media(QJsonObject &);
	~Media() = default;

	Media &operator=(const Media &other);
	operator QJsonObject() const override;

	MD5 id() const;
	void setId(MD5 id);
	MediaPlayerGlobal::MediaRole role() const;
	void setRole(MediaPlayerGlobal::MediaRole role);
	QString path() const;
	QList<QString> paths() const;
	void setPath(QString path);
	void removePath(QString path);
	int nbPath() const;
	bool isAvailable() const;
	int count() const;
	void setCount(int count);
	int rating() const;
	void setRating(int rate);
	QDate added() const;
	void setAdded(QDate added);
	QDateTime lastFinish() const;
	void setLastFinish(QDateTime lastFinish);
	double currentRead() const;
	void setCurrentRead(double currentRead);
	QDateTime lastProbed() const;
	void setLastProbed(QDateTime);

	static MediaPointer createMedia(MD5, QString path = "");

signals:
	void countChanged();
	void ratingChanged();
	void currentReadChanged();
	void lastFinishChanged();
	void isAvailableChanged();
	void lastProbedChanged();

	void mediaChanged();
};

Q_DECLARE_METATYPE(Media)
