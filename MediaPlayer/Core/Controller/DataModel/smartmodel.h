#pragma once

#include <QAbstractListModel>

#include <Model/Smart/smartgroup.h>

class SmartModel : public QAbstractListModel
{
    Q_OBJECT
    enum class SmartRole {OpRole = Qt::UserRole + 1, TypeRole};
private:
    SmartGroup* m_model;

public:
    explicit SmartModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &, const QVariant &,
                 int = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setModel(SmartGroup*);
private:
};

