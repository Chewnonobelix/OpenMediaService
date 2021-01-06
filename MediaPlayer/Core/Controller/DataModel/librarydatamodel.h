#ifndef LIBRARYDATAMODEL_HPP
#define LIBRARYDATAMODEL_HPP

#include "../Core/abstractcontroller.h"
#include "Model/global.h"
#include "Model/library.h"
#include <QAbstractListModel>
#include <QtCore/qglobal.h>

class LibraryDataModel : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
								 currentIndexChanged)

private:
	enum LibraryRoles {
		MediaRole = Qt::UserRole + 1,
		NameRole,
		IndexRole,
		IdRole
	};
	QList<LibraryPointer> m_libraries;
	int m_currentIndex = -1;

protected:
	QHash<int, QByteArray> roleNames() const override;

public:
	LibraryDataModel();
	LibraryDataModel(const LibraryDataModel &);
	~LibraryDataModel() = default;

	LibraryDataModel &operator=(const LibraryDataModel &);

	friend bool operator!=(const LibraryDataModel &, const LibraryDataModel &);

	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	void insertData(LibraryPointer);
	void sort(int, Qt::SortOrder) override;

	Q_INVOKABLE Library *at(int);
	Q_INVOKABLE void clear();
	void setCurrentIndex(int);
	int currentIndex() const;

public slots:
	void onUpdateLibraries();

signals:
	void currentIndexChanged();
	void currentModelChanged(LibraryPointer);
};

Q_DECLARE_METATYPE(LibraryDataModel)

#endif // LIBRARYDATAMODEL_HPP
