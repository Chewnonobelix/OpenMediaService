#pragma once

#include "abstractcontroller.h"

class ControllerSettings: public AbstractController
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerSettings)

public:
    ControllerSettings() = default;
    ~ControllerSettings() = default;
};

