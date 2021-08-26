#pragma once

#include <QQmlExtensionPlugin>

class AudioPlugin : public QQmlExtensionPlugin {
	Q_OBJECT

public:
	void registerTypes(const char *uri) override;
};
