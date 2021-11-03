#pragma once

#include <QTemporaryDir>
#include <QProcess>
#include <QAbstractListModel>
#include <QImage>

#include <Model/media.h>

class ComicsPlayer: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ComicsPlayer)

    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged)
    Q_PROPERTY(bool rightToLeft READ rightToLeft NOTIFY rightToLeftChanged)

    enum class ComicsPlayerRole {PageRole = Qt::UserRole + 1};
private:
    QTemporaryDir* m_dir = nullptr;
    MediaPointer m_media;
    QList<QString> m_pages;
    bool m_split = false;

    void build();
public:
    ComicsPlayer(QObject* = nullptr);
    ~ComicsPlayer() override;

    bool play(MediaPointer);

    int currentPage() const;
    void setCurrentPage(int);
    int pageCount() const;
    bool rightToLeft() const;
    bool split() const;
    void setSplit(bool);

    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
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

