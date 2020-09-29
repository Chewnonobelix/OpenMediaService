#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary(QQmlEngine &engine)
{
    auto *context = engine.rootContext();
    context->setContextProperty("_libraryModel", &ldm);
    context->setContextProperty("_libraries", this);
}

ControllerLibrary::ControllerLibrary(const ControllerLibrary &) : AbstractController() {}

void ControllerLibrary::onAddLibrary(LibraryPointer p)
{
    ldm.insertData(p);
    //    auto list = db()->selectLibrary();

    //    QList<Library *> model;
    //    for (auto it : list)
    //        model << it.data();

    //    std::sort(model.begin(), model.end(), [](Library *l1, Library *l2) {
    //        return l1->role() < l2->role() && l1->name() < l2->name();
    //    });

    //    emit libraryModelChanged(model);
}

void ControllerLibrary::exec()
{
    for (auto it : db()->selectLibrary())
        ldm.insertData(it);

    connect(db(), &InterfaceSaver::addLibrary, this, &ControllerLibrary::onAddLibrary);
}
