#pragma once

#include <QTemporaryDir>
#include <QProcess>
#include <QAbstractListModel>

#include <Model/media.h>

class ComicsPlayer: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ComicsPlayer)

    enum class ComicsPlayerRole {PageRole = Qt::UserRole + 1};
private:
    QTemporaryDir* m_dir = nullptr;
    MediaPointer m_media;
    QList<QString> m_pages;
public:
    ComicsPlayer(QObject* = nullptr);
    ~ComicsPlayer() override;

    bool play(MediaPointer);

public:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex&, int = Qt::DisplayRole) const override;
};

