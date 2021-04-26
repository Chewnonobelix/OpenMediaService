#pragma once

#include <QSettings>

#include "abstractcontroller.h"

class ControllerSettings: public AbstractController
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerSettings)

private:
    QPointer<QSettings> m_settings;

public:
    ControllerSettings() = default;
    ~ControllerSettings() = default;

    void exec() override;
};

