#ifndef CONTROLLERLIBRARY_HPP
#define CONTROLLERLIBRARY_HPP

#include "../DataModel/librarydatamodel.h"
#include "abstractcontroller.h"
#include <QQmlContext>
#include <QtCore/qglobal.h>
class ControllerLibrary : public AbstractController
{
 Q_OBJECT
 Q_PROPERTY(
  Library *currentLibrary READ currentLibrary WRITE setCurrentLibrary NOTIFY currentLibraryChanged)

 private:
 Library *m_currentLibrary;

 public:
 ControllerLibrary(QQmlEngine &);
 ControllerLibrary(const ControllerLibrary &);
 ~ControllerLibrary() = default;

 void exec() override;

 Library *currentLibrary() const;
 void setCurrentLibrary(Library *);

 signals:
 void currentLibraryChanged();
};

#endif // CONTROLLERLIBRARY_HPP
