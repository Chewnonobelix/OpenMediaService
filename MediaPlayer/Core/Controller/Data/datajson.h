#pragma once

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <mediaplayercore_global.h>

#include "interfacesaver.h"

class MEDIAPLAYERCORE_EXPORT DataJson : public InterfaceSaver {
	Q_OBJECT

private:
	LibraryPointer open(QString) const;
	void write(LibraryPointer) const;

public:
	DataJson() = default;
	~DataJson() override = default;
	DataJson(const DataJson &);

	virtual void init() override;

public slots:
	virtual QMap<QUuid, LibraryPointer> selectLibrary() const override;
	virtual bool createLibrary(QString, MediaPlayerGlobal::MediaRole) override;
	virtual bool removeLibrary(QString) override;
	virtual bool updateLibrary(LibraryPointer) override;
};

Q_DECLARE_METATYPE(DataJson)
