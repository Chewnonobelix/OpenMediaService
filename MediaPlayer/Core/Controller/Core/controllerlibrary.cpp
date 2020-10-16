#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary(QQmlEngine &engine)
{
    auto *context = engine.rootContext();
    context->setContextProperty("_libraries", this);
}

ControllerLibrary::ControllerLibrary(const ControllerLibrary &) : AbstractController() {}

void ControllerLibrary::onLibrariesChanged()
{
}

void ControllerLibrary::exec()
{
    onLibrariesChanged();

    connect(db(),
            &InterfaceSaver::librariesChanged,
            this,
            &ControllerLibrary::onLibrariesChanged,
            Qt::UniqueConnection);
}
