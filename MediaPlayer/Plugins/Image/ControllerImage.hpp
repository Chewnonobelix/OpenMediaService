#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

class ControllerImage : public AbstractController, public InterfacePlugins {
public:
	ControllerImage();
};
