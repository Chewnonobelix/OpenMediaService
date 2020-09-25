#ifndef LIBRARYDATAMODEL_HPP
#define LIBRARYDATAMODEL_HPP

#include "Model/global.h"
#include "Model/library.h"
#include <QAbstractListModel>
#include <QtCore/qglobal.h>

class LibraryDataModel : public QAbstractListModel
{
    Q_OBJECT

private:
    enum LibraryRoles { MediaRole = Qt::UserRole + 1, NameRole, IndexRole };
    QList<LibraryPointer> m_libraries;
    int m_currentIndex = -1;

protected:
    QHash<int, QByteArray> roleNames() const override;

public:
    LibraryDataModel() = default;
    LibraryDataModel(const LibraryDataModel &);
    ~LibraryDataModel() = default;

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void insertData(LibraryPointer);
    Q_INVOKABLE Library *at(int);
};

Q_DECLARE_METATYPE(LibraryDataModel)

#endif // LIBRARYDATAMODEL_HPP
