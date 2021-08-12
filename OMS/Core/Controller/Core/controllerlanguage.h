#pragma once

#include <QTranslator>
#include <QDir>
#include <QLoggingCategory>
#include <QCoreApplication>

class ControllerLanguage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerLanguage)

private:
    QTranslator m_translator;

    QList<QString> m_language;

public:
    ControllerLanguage();
    ~ControllerLanguage() = default;

    bool setLanguageList(QStringList);
    Q_INVOKABLE QStringList languageList() const;

    bool load(QString);
};

