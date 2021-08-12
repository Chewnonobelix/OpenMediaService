#pragma once

#include <QTranslator>

class ControllerLanguage
{
    Q_GADGET

private:
    QTranslator m_translator;

    QList<QString> m_language;

public:
    ControllerLanguage() = default;
    ~ControllerLanguage() = default;

    bool setLanguageList(QStringList);
    Q_INVOKABLE QStringList languageList() const;

    bool load(QString);
};

