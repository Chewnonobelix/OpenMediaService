#pragma once

#include <QQmlExtensionPlugin>

class EBookPlugin : public QQmlExtensionPlugin {
	Q_OBJECT

public:
	void registerTypes(const char *uri) override;
};
