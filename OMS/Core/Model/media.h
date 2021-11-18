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
#include <QEnableSharedFromThis>

#include <mediaplayercore_global.h>

#include "designpattern.h"
#include "global.h"
#include "metadata.h"

using namespace DesignPattern;

class Media;

typedef QSharedPointer<Media> MediaPointer;

class MEDIAPLAYERCORE_EXPORT Media : public QObject, public MetaData, public QEnableSharedFromThis<Media> {
	Q_OBJECT

    Q_PROPERTY(QUuid id READ id CONSTANT)
	Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
	Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role CONSTANT)
	Q_PROPERTY(bool isAvailable READ isAvailable NOTIFY isAvailableChanged)
	Q_PROPERTY(QDate added READ added CONSTANT)
	Q_PROPERTY(QDateTime lastFinish READ lastFinish NOTIFY lastFinishChanged)
	Q_PROPERTY(double currentRead READ currentRead WRITE setCurrentRead NOTIFY
								 currentReadChanged)
    Q_PROPERTY(QStringList paths READ paths CONSTANT)
	Q_PROPERTY(int rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(QStringList tags READ tags NOTIFY tagsChanged)

private:
	QSet<QString> m_path;

	void set();

public:
	enum class CompareState { EqualState, InferiorState, SuperiorState };
	
	Media(MD5 = "", QString = "");
	Media(const Media &other);
    Media(QUuid);
	using MetaData::MetaData;
	Media(QJsonObject &);
	~Media() = default;

	Media &operator=(const Media &other);
	operator QJsonObject() const override;
    friend MEDIAPLAYERCORE_EXPORT CompareState compare(MediaPointer, MediaPointer, QString);
	
    QUuid id() const;
    bool setId(QUuid id);
    MD5 fingerprint() const;
    void setFingerprint(MD5);
	MediaPlayerGlobal::MediaRole role() const;
    bool setRole(MediaPlayerGlobal::MediaRole role);
	QString path() const;
	QList<QString> paths() const;
    bool setPath(QString path);
    bool removePath(QString path);
	int nbPath() const;
	bool isAvailable() const;
	int count() const;
    bool setCount(int count);
	int rating() const;
    bool setRating(int rate);
	QDate added() const;
    bool setAdded(QDate added);
	QDateTime lastFinish() const;
    bool setLastFinish(QDateTime lastFinish);
	double currentRead() const;
    bool setCurrentRead(double currentRead);
	QDateTime lastProbed() const;
    bool setLastProbed(QDateTime);
    Q_INVOKABLE bool hasTag(QString) const;
    QStringList tags() const;
    void setTags(QStringList);
    Q_INVOKABLE void setTag(QString);

	static MediaPointer createMedia(MD5, QString path = "");

signals:
	void countChanged();
	void ratingChanged();
	void currentReadChanged();
	void lastFinishChanged();
	void isAvailableChanged();
	void lastProbedChanged();
    void tagsChanged();

	void mediaChanged();
};

Q_DECLARE_METATYPE(Media)
