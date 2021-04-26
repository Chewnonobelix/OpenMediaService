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
    enum class PluginRole {NameRole = Qt::DisplayRole +1, EnableRole};

	QMap<MediaRole, QSharedPointer<InterfacePlugins>> m_plugins;

public:
	PluginManager() = default;
	~PluginManager() = default;

	void init();

	QSharedPointer<InterfacePlugins> operator[](MediaRole) const;

    int rowCount(QModelIndex const& = QModelIndex()) const override;
    QVariant data(const QModelIndex & , int = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
};
