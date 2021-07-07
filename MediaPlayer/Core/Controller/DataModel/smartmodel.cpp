#include "smartmodel.h"

SmartModel::SmartModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int SmartModel::columnCount(const QModelIndex&) const
{
    return m_depth + 1;
}

int SmartModel::rowCount(const QModelIndex &) const
{
    return m_model ? m_flat.count() : 0;
}

QVariant SmartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto model = m_flat[index.row()];

    //    auto group = model.dynamicCast<SmartGroup>();
    //    auto rule = model.dynamicCast<SmartRule>();

    switch(SmartRole(role)) {
    case SmartRole::TypeRole:
        return index.column() == model.depth ? model.type : QVariant();
    default:
        break;
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

void SmartModel::setModel(SmartGroup* m)
{
    m_model = m;
}

QHash<int, QByteArray> SmartModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(SmartRole::OpRole), "op"},
                                         {int(SmartRole::TypeRole), "type"},
                                         {int(SmartRole::FieldRole), "field"},

                                        };

    return ret;
}

SmartGroup* SmartModel::group() const
{
    return m_model;
}

void SmartModel::setGroup(SmartGroup* g)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount() - 1);
    endRemoveRows();

    beginRemoveColumns(QModelIndex(), 0, columnCount());
    removeColumns(0, columnCount() - 1);
    endRemoveColumns();

    m_model = g;
    m_flat = toFlat(*m_model);
    emit groupChanged();

    beginInsertRows(QModelIndex(), 0, rowCount() + 1);
    insertRows(0, rowCount() + 1);
    endInsertRows();
    beginInsertColumns(QModelIndex(), 0, columnCount() + 1);
    insertColumns(0, columnCount() + 1);
    endInsertColumns();
    qDebug()<<"depth"<<m_depth<<m_flat.count();

    for(auto it: m_flat)
        qDebug()<<it.depth<<it.type<<it.rule.dynamicCast<SmartRule>()<<it.rule.dynamicCast<SmartGroup>();
}

QList<SmartModel::Flat> SmartModel::toFlat(SmartGroup& g, int depth)
{
    m_depth = std::max(m_depth, depth);

    QList<SmartModel::Flat> ret;
    ret << Flat{depth-1, "group", QSharedPointer<SmartGroup>::create(g)};
    for(auto i = 0; i < g.count(); i++) {
        if(!(g)[i].dynamicCast<SmartRule>().isNull()) {
            ret << Flat{depth, "rule", (g)[i]};
        }
        else {
            ret << toFlat(*(g)[i].dynamicCast<SmartGroup>(), depth+1);
        }
    }
    return ret;
}
