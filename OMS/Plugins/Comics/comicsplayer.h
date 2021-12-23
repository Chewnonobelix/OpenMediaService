#pragma once

#include <QTemporaryDir>
#include <QProcess>
#include <QAbstractListModel>
#include <QImage>

#include <Model/media.h>
#include "comicsmedia.h"

class ComicsPlayer: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ComicsPlayer)

    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged)
    Q_PROPERTY(bool rightToLeft READ rightToLeft NOTIFY rightToLeftChanged)

    enum class ComicsPlayerRole {PageRole = Qt::UserRole + 1};

private:
    ComicsMedia m_media;
    QList<QString> m_pages;
    bool m_split = false;

    void build();
    QString baseName(QString) const;

public:
    ComicsPlayer(QObject* = nullptr);
    ~ComicsPlayer() override;

    bool play(ComicsMedia);

    int currentPage() const;
    void setCurrentPage(int);
    int pageCount() const;
    bool rightToLeft() const;
    bool split() const;
    void setSplit(bool);

    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void addPageTag(QString, QString);
    Q_INVOKABLE void removePageTag(QString, QString);
    Q_INVOKABLE QStringList pageTags(QString) const;

    Q_INVOKABLE QStringList bookmarks() const;
    Q_INVOKABLE bool addBookmark(QString);
    Q_INVOKABLE bool removeBookmark(QString);
    Q_INVOKABLE bool loadBookmark(QString);
public:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex&, int = Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int = Qt::DisplayRole) override;

signals:
    void currentPageChanged();
    void pageCountChanged();
    void rightToLeftChanged();
    void splitChanged();
};

