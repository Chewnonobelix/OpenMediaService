#pragma once

#include <QMap>
#include <QPluginLoader>
#include <QAbstractListModel>

#include "interfaceplugins.h"
#include <Model/global.h>

class PluginManager: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(PluginManager)

private:
    struct Plugin {
        QString name;
        MediaRole role;
        QSharedPointer<InterfacePlugins> plugin;
        bool enable;
    };

    enum class PluginRole {NameRole = Qt::DisplayRole +1, EnableRole, RoleRole, SettingsViewRole};

    QMap<MediaRole, QPair<QSharedPointer<InterfacePlugins>, bool>> m_plugins;
    QList<Plugin> m_liste;

public:
	PluginManager() = default;
    ~PluginManager() = default;

    void init();

	QSharedPointer<InterfacePlugins> operator[](MediaRole) const;

    int rowCount(QModelIndex const& = QModelIndex()) const override;
    QVariant data(const QModelIndex & , int = Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QStringList pluginsName() const;
    Q_INVOKABLE MediaRole pluginRole(QString) const;
    Q_INVOKABLE bool pluginEnable(QString) const;

};
