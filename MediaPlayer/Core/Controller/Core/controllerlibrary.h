#ifndef CONTROLLERLIBRARY_HPP
#define CONTROLLERLIBRARY_HPP

#include "../DataModel/librarydatamodel.h"
#include "abstractcontroller.h"
#include <QQmlContext>
#include <QtCore/qglobal.h>
class ControllerLibrary : public AbstractController
{
    Q_OBJECT
private:
    LibraryDataModel ldm;

public:
    ControllerLibrary(QQmlEngine &);
    ControllerLibrary(const ControllerLibrary &);
    ~ControllerLibrary() = default;

    void exec() override;

public slots:
    void onAddLibrary(LibraryPointer = LibraryPointer());

signals:
    void libraryModelChanged(QList<Library *>);
};

#endif // CONTROLLERLIBRARY_HPP
