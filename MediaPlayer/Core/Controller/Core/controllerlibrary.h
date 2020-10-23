#ifndef CONTROLLERLIBRARY_HPP
#define CONTROLLERLIBRARY_HPP

#include "../DataModel/librarydatamodel.h"
#include "abstractcontroller.h"
#include <QQmlContext>
#include <QtCore/qglobal.h>
#include "liveqmlengine.h"

class ControllerLibrary : public AbstractController
{
 Q_OBJECT
 Q_PROPERTY(Library *currentLibrary READ currentLibrary NOTIFY currentLibraryChanged)

 private:
 LibraryPointer m_currentLibrary;

 public:
 ControllerLibrary();
 ControllerLibrary(const ControllerLibrary &);
 ~ControllerLibrary() = default;

 void exec() override;

 Library *currentLibrary() const;
 Q_INVOKABLE void setCurrentLibrary(QString);

 Q_INVOKABLE void open();

 Q_INVOKABLE void addSourceDir(QString);
 signals:
 void currentLibraryChanged();
};

#endif // CONTROLLERLIBRARY_HPP
