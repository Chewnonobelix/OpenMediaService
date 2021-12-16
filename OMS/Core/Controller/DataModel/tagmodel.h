#pragma once

#include <QAbstractListModel>

class TagModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(TagModel)

    enum class TagRole {};

public:
    explicit TagModel(QObject *parent = nullptr);
    ~TagModel() override = default;

    bool addTag(Qstring);
    bool editTag(QUuid, QString);
    bool removeTag(QUuid);

public:
    // Basic functionality:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:

signals:
    void s_addTag(QString);
    void s_editTag(QUuid, QString);
    void s_removeTag(QUuid);
};

