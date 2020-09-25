#ifndef CONTROLLERLIBRARY_HPP
#define CONTROLLERLIBRARY_HPP

#include "../DataModel/librarydatamodel.h"
#include "abstractcontroller.h"
#include <QtCore/qglobal.h>

class ControllerLIbrary : public AbstractController
{
    Q_OBJECT
private:
    LibraryDataModel ldm;

public:
    ControllerLIbrary();
};

#endif // CONTROLLERLIBRARY_HPP
