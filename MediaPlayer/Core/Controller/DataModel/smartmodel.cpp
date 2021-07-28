#include "smartmodel.h"

SmartModel::SmartModel(PluginManager & manager, QObject *parent)
    : QAbstractTableModel(parent), m_manager(manager)
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

    switch(SmartRole(role)) {
    case SmartRole::TypeRole:
        return index.column() == model.depth ? model.type : QVariant();
    case SmartRole::IdRole:
        return model.rule->id();
    case SmartRole::FieldsRole:
        return m_types.keys();
    case SmartRole::OpRole:
        return keyToString(model.rule->op());
    case SmartRole::FieldRole:
        return model.rule.dynamicCast<SmartRule>()->field();
    case SmartRole::ValueRole:
        return model.rule.dynamicCast<SmartRule>()->value();
    default:
        break;
    }

    return QVariant();
}

bool SmartModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        auto model = m_flat[index.row()].rule;
        switch(SmartRole(role)) {
        case SmartRole::FieldRole:
            model.dynamicCast<SmartRule>()->setField(value.toString());
            break;
        case SmartRole::OpRole:
            model->setOp(stringToOp(value.toString()));
            break;
        case SmartRole::ValueRole:
            model.dynamicCast<SmartRule>()->setValue(value);
            break;
        default:
            return false;
            break;
        }
        emit groupChanged();

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

QHash<int, QByteArray> SmartModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(SmartRole::OpRole), "op"},
                                         {int(SmartRole::TypeRole), "type"},
                                         {int(SmartRole::FieldsRole), "fields"},
                                         {int(SmartRole::FieldRole), "field"},
                                         {int(SmartRole::ValueRole), "value"},
                                         {int(SmartRole::IdRole), "id"}
                                        };

    return ret;
}

SmartGroup* SmartModel::group() const
{
    return m_model.data();
}

void SmartModel::setModel(SmartGroupPointer g)
{
    clear();
    m_model = g;
    m_flat = toFlat(m_model);
    restore();
}

QList<SmartModel::Flat> SmartModel::toFlat(SmartGroupPointer g, int depth)
{
    m_depth = std::max(m_depth, depth);

    QList<SmartModel::Flat> ret;
    ret << Flat{depth-1, "group", g};

    for(auto i = 0; i < g->count(); i++) {
        if(!(*g)[i].dynamicCast<SmartRule>().isNull()) {
            ret << Flat{depth, "rule", (*g)[i]};
        }
        else {
            ret << toFlat((*g)[i].dynamicCast<SmartGroup>(), depth+1);
        }
    }

    return ret;
}

void SmartModel::add(int row, bool group)
{
    clear();

    auto g = m_flat[row].rule.dynamicCast<SmartGroup>();
    if(!g.isNull()) {
        g->add(group);
    }

    m_flat = toFlat(m_model);

    emit groupChanged();

    restore();
}

bool SmartModel::remove(QString i)
{
    clear();

    auto count = m_flat.count();

    auto it = std::find_if(m_flat.begin(), m_flat.end(), [i](Flat f) {
            return f.rule->id() == QUuid::fromString(i);
});


    auto ret = (it != m_flat.end()) && it->rule->parent() ? it->rule->parent().dynamicCast<SmartGroup>()->remove(QUuid::fromString(i)) : false;
    m_flat.clear();
    m_flat = toFlat(m_model);
    emit groupChanged();

    restore();

    return ret && m_flat.count() == count -1;
}

void SmartModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount() - 1);
    endRemoveRows();

    beginRemoveColumns(QModelIndex(), 0, columnCount());
    removeColumns(0, columnCount() - 1);
    endRemoveColumns();
}

void SmartModel::restore()
{
    beginInsertRows(QModelIndex(), 0, rowCount() + 1);
    insertRows(0, rowCount() + 1);
    endInsertRows();

    beginInsertColumns(QModelIndex(), 0, columnCount() + 1);
    insertColumns(0, columnCount() + 1);
    endInsertColumns();
}

void SmartModel::setRole(MediaPlayerGlobal::MediaRole r)
{
    m_role = r;

    QFile f("./Rules/"+m_manager[r]->rules());
    f.open(QIODevice::ReadOnly);
    auto json = QJsonDocument::fromJson(f.readAll());
    f.close();
    m_types.clear();
    auto array = json.array();

    for(auto it: array) {
        if(it.toObject()["smart"].toBool(false))
            m_types[it.toObject()["name"].toString()] = it.toObject()["type"].toVariant().value<MediaPlayerGlobal::Type>();
    }
}

QList<QString> SmartModel::ops(QString field) const
{
    auto type = m_types[field];
    auto opss = AbstractRule::s_ops.values(type);
    QStringList ret;
    for(auto it: opss) {
        ret<<keyToString(it);
    }
    return ret;
}

QString SmartModel::keyToString(AbstractRule::Op op) const
{
    QString ret;
    switch (op)
    {
    case AbstractRule::Op::Equal:
        ret = "Equal";
        break;
    case AbstractRule::Op::Superior:
        ret = "Superior";
        break;
    case AbstractRule::Op::Inferior:
        ret = "Inferior";
        break;
    case AbstractRule::Op::Not:
        ret = "Not";
        break;
    case AbstractRule::Op::InferiorEqual:
        ret = "Inferior or equal";
        break;
    case AbstractRule::Op::SuperiorEqual:
        ret = "Superior or equal";
        break;
    case AbstractRule::Op::Limit:
        ret = "Limit";
        break;
    case AbstractRule::Op::And:
        ret = "And";
        break;
    case AbstractRule::Op::Or:
        ret = "Or";
        break;
    case AbstractRule::Op::List:
        ret = "List";
        break;
    case AbstractRule::Op::RegExp:
        ret = "Regular expression";
        break;
    case AbstractRule::Op::Contain:
        ret = "Contain";
        break;
    case AbstractRule::Op::Start:
        ret = "Start with";
        break;
    case AbstractRule::Op::End:
        ret = "End with";
        break;
    case AbstractRule::Op::Undefined:
        break;
    }
    return ret;
}

AbstractRule::Op SmartModel::stringToOp(QString text) const
{
    auto ret = AbstractRule::Op::Undefined;

    if(text == "Superior")
        ret = AbstractRule::Op::Superior;
    else if(text == "Inferior")
        ret = AbstractRule::Op::Inferior;
    else if(text == "Equal")
        ret = AbstractRule::Op::Equal;
    else if(text == "Not")
        ret = AbstractRule::Op::Not;
    else if(text == "Inferior or equal")
        ret = AbstractRule::Op::InferiorEqual;
    else if(text == "Superior or equal")
        ret = AbstractRule::Op::SuperiorEqual;
    else if(text == "Limit")
        ret = AbstractRule::Op::Limit;
    else if(text == "And")
        ret = AbstractRule::Op::And;
    else if(text == "Or")
        ret = AbstractRule::Op::Or;
    else if(text == "List")
        ret = AbstractRule::Op::List;
    else if(text == "Regular expression")
        ret = AbstractRule::Op::RegExp;
    else if(text == "Contain")
        ret = AbstractRule::Op::Contain;
    else if(text == "Start with")
        ret = AbstractRule::Op::Start;
    else if(text == "End with")
        ret = AbstractRule::Op::End;

    return ret;
}
