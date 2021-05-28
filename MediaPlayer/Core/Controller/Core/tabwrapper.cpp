#include "tabwrapper.h"

QUuid TabWrapper::create()
{
    return QUuid();
}

QPointer<TabManager> TabWrapper::get(QUuid)
{
    return nullptr;
}
