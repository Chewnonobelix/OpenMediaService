#pragma once

#include <QAbstractListModel>
#include <QtCore/qglobal.h>

#include "../../mediaplayercore_global.h"

#include <Controller/Data/interfacesaver.h>
#include <Controller/Core/controllerlibrary.h>

#include "Model/global.h"
#include "Model/library.h"

struct Data {
    LibraryPointer library;
    QPointer<ControllerLibrary> controller;
};

class MEDIAPLAYERCORE_EXPORT LibraryDataModel : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
								 currentIndexChanged)

private:
	enum LibraryRoles {
		MediaRole = Qt::UserRole + 1,
		NameRole,
		IndexRole,
        IdRole,
        ControllerRole
	};
    static QList<Data> m_libraries;
	int m_currentIndex = -1;

protected:
	QHash<int, QByteArray> roleNames() const override;

public:
	LibraryDataModel();
	LibraryDataModel(const LibraryDataModel &);
	~LibraryDataModel() = default;

	LibraryDataModel &operator=(const LibraryDataModel &);
	LibraryPointer operator[](QUuid) const;

	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	void insertData(LibraryPointer);
	void sort(int, Qt::SortOrder) override;

	Q_INVOKABLE Library *at(int);
    Q_INVOKABLE ControllerLibrary * controller(int);
	Q_INVOKABLE void clear();
	void setCurrentIndex(int);
	int currentIndex() const;
	int indexOf(LibraryPointer) const;

public slots:
	void onUpdateLibraries();

signals:
	void currentIndexChanged();
	void currentModelChanged(LibraryPointer);
};

Q_DECLARE_METATYPE(LibraryDataModel)
