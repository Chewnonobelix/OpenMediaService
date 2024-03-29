#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>
#include <Controller/DataModel/playlistlistmodel.h>
#include <Controller/DataModel/orderdisplaymodel.h>
#include "librairyimagemodel.h"

class ControllerImage : public AbstractController, public InterfacePlugins {
	Q_OBJECT
	Q_INTERFACES(InterfacePlugins)
    Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Image")
    Q_DISABLE_COPY(ControllerImage)

    Q_PROPERTY(OrderDisplayModel* orderModel READ orderModel CONSTANT)

private:
	PlaylistPointer m_current;

    LibrairyImageModel m_model;
    PlaylistListModel m_listModel;
    QPointer<OrderDisplayModel> m_orderModel;

	QTimer m_timer;
    static QPointer<QQmlComponent> s_playlist;
    static QPointer<QQmlComponent> s_player;
    QPointer<QObject> m_playlistObj;
    QPointer<QObject> m_playerObj;
    QQmlContext*  context = nullptr;

public:
	ControllerImage() = default;
	~ControllerImage() override = default;

	void exec() override;

    QObject * playerView() const override;
    QObject *playlistView() override;
    QUrl settingsView() const override;

    void configureLibrary(LibraryPointer) override;
    void setPlaylist(PlaylistPointer) override;
	void setMedia(MediaPointer) override;
    QMap<QString, QObject*> displayProperty() override;

	MediaRole role() const override;
	QStringList filters() const override;
    QString rules() const override;
    inline QList<QSharedPointer<InterfaceImporter>> importers() const override{
        return  QList<QSharedPointer<InterfaceImporter>>();
    }

    QSharedPointer<InterfacePlugins> clone() const override;
    OrderDisplayModel* orderModel();

public slots:
	void onCurrentIndexChanged(int);
    void playing(int = -1);
	void stop();
	void onTimeout();
    void onPlaylistChanged();

signals:
    void play(QString);
};
