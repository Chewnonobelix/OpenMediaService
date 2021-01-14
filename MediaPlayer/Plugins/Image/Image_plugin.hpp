#pragma once

#include <QQmlExtensionPlugin>

class ImagePlugin : public QQmlExtensionPlugin {
	Q_OBJECT

public:
	void registerTypes(const char *uri) override;
};
