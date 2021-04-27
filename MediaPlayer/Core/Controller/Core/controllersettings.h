#pragma once

#include <QSettings>

#include "mediaplayercore_global.h"

#include "abstractcontroller.h"

class MEDIAPLAYERCORE_EXPORT ControllerSettings: public AbstractController
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerSettings)

private:
    QPointer<QSettings> m_settings;

public:
    ControllerSettings() = default;
    ~ControllerSettings() = default;

    void exec() override;

    Q_INVOKABLE void display();
};

