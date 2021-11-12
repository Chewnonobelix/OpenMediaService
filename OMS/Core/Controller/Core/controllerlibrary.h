#pragma once

#include <QLoggingCategory>

#include <Controller/Core/abstractcontroller.h>
#include <Controller/DataModel/playlistmodel.h>

#include <Model/library.h>

Q_DECLARE_LOGGING_CATEGORY(librarylog)

class ControllerLibrary : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerLibrary)

	Q_PROPERTY(PlaylistModel *playlist READ playlist)
    Q_PROPERTY(Library *currentLibrary READ library NOTIFY libraryChanged)
	Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QList<QVariantMap> importers READ importers CONSTANT)

private:
	LibraryPointer m_current = nullptr;
    PlaylistModel m_playlist;

	QUuid m_id = QUuid::createUuid();

    QMap<QUuid, QSharedPointer<InterfacePlugins>> m_plugins;

	Library *library() const;
    PlaylistModel *playlist() ;

public:
	ControllerLibrary() = default;
    ~ControllerLibrary() = default;

	Q_INVOKABLE void exec() override;

    Q_INVOKABLE void setCurrentLibrary(LibraryPointer);

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);
    Q_INVOKABLE QUuid addPlaylist(bool = false);
	Q_INVOKABLE void removePlaylist(QString);
    QList<QVariantMap> importers() const;

    QString id() const;
    bool containView(QUuid) const;
    void setModelIndex(int);
    Q_INVOKABLE void importFrom(QString, QString);

public:
    Q_INVOKABLE void setPlaylistIndex(QString, int);
    Q_INVOKABLE QObject *playerComp(QString);
    Q_INVOKABLE QObject* playlistComp(QString = "");

public slots:
	void onUpdateLibrary();
    void onCurrentPlaylistChanged();

signals:
	void libraryChanged();
};
