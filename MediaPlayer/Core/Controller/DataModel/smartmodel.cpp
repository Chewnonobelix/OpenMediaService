#include "smartmodel.h"

SmartModel::SmartModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int SmartModel::rowCount(const QModelIndex &) const
{
    return m_model->count();
}

QVariant SmartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto model = (*m_model)[index.row()];

    auto group = model.dynamicCast<SmartGroup>();
    auto rule = model.dynamicCast<SmartRule>();

    switch(SmartRole(role)) {
    case SmartRole::OpRole:
        return !group.isNull() ? QVariant::fromValue(group->op()) : QVariant();
    case SmartRole::TypeRole:
        return group.isNull() ? "rule" : "group";
    }

    return QVariant();
}

bool SmartModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void SmartModel::setModel(SmartGroup * m)
{
    m_model = m;
}

QHash<int, QByteArray> SmartModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(SmartRole::OpRole), "op"},
                                         {int(SmartRole::TypeRole), "type"}

                                        };

    return ret;
}
