#pragma once

#include <QQmlExtensionPlugin>

class ComicsPlugin : public QQmlExtensionPlugin {
	Q_OBJECT

public:
	void registerTypes(const char *uri) override;
};
