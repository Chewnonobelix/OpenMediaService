#pragma once
#include <QQmlContext>
#include <QtCore/qglobal.h>

#include "../DataModel/PlaylistModel.hpp"
#include "../DataModel/librarydatamodel.h"

#include "abstractcontroller.h"
#include "liveqmlengine.h"

class ControllerLibrary : public AbstractController {
	Q_OBJECT
	Q_PROPERTY(
			Library *currentLibrary READ currentLibrary NOTIFY currentLibraryChanged)

private:
	LibraryPointer m_currentLibrary;
	LibraryDataModel m_librariesModel;
	PlaylistModel m_playlistModel;

public:
	ControllerLibrary();
	ControllerLibrary(const ControllerLibrary &);
	~ControllerLibrary() = default;

	void exec() override;

	Library *currentLibrary() const;
	Q_INVOKABLE void setCurrentLibrary(QString);

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);

signals:
	void currentLibraryChanged();

public slots:
	void onCurrentModelChanged(LibraryPointer);
	void onMediaChanged();
	void onCurrentPlaylistChanged();
};
