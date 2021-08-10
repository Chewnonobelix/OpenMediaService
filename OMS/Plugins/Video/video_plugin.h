#pragma once

#include <QQmlExtensionPlugin>

class VideoPlugin : public QQmlExtensionPlugin {
	Q_OBJECT

public:
	void registerTypes(const char *uri) override;
};
