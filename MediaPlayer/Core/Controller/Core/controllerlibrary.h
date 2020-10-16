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

public:
    ControllerLibrary(QQmlEngine &);
    ControllerLibrary(const ControllerLibrary &);
    ~ControllerLibrary() = default;

    void exec() override;

public slots:
    void onLibrariesChanged();
};

#endif // CONTROLLERLIBRARY_HPP
