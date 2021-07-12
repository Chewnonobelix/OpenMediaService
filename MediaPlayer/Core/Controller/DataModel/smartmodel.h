#pragma once

#include <QAbstractListModel>
#include <QJsonDocument>

#include <Model/Smart/smartgroup.h>
#include <Controller/Plugins/pluginmanager.h>

class SmartModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(MediaPlayerGlobal::MediaRole role WRITE setRole)

    enum class SmartRole {OpRole = Qt::UserRole + 1, TypeRole, FieldRole, IdRole};

    struct Flat {
      int depth = 0;
      QString type;
      QSharedPointer<AbstractRule> rule;
    };


private:
    SmartGroupPointer m_model;
    QList<Flat> m_flat;
    int m_depth = 0;
    MediaPlayerGlobal::MediaRole m_role;
    PluginManager& m_manager;
    QMap<QString, AbstractRule::Type> m_types;

    QList<Flat> toFlat(SmartGroupPointer, int = 1);

    void clear();
    void restore();

public:
    explicit SmartModel(PluginManager&, QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &, const QVariant &,
                 int = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setModel(SmartGroupPointer);
    Q_INVOKABLE void add(int, bool);
    Q_INVOKABLE bool remove(QString);
    void setRole(MediaPlayerGlobal::MediaRole);
    Q_INVOKABLE QList<QString> ops(QString) const;
public:
    SmartGroup* group() const;

signals:
    void groupChanged();

private:
};

