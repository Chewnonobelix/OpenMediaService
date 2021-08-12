#include "controllerlanguage.h"

Q_LOGGING_CATEGORY(languagelog, "library.log")

ControllerLanguage::ControllerLanguage(): QObject(nullptr)
{
    QDir dir;
    dir.cd("Tr");
    auto infos = dir.entryInfoList({"*.qm"}, QDir::Filter::Files);

    for(auto it: infos) {
        qCDebug(languagelog)<<"Found translation"<<it.absoluteFilePath();
        m_language<<it.absoluteFilePath();
    }

    QCoreApplication::installTranslator(&m_translator);
}

bool ControllerLanguage::setLanguageList(QStringList list)
{
    auto ret = m_language != list;

    if(ret)
        m_language = list;

    return ret;
}

QStringList ControllerLanguage::languageList() const
{
    QStringList ret;

    for(auto it: m_language) {
        ret<<it.split("/").last().split(".").first();
    }

    return ret;
}

bool ControllerLanguage::load(QString language)
{
    return m_translator.load(language, "Tr");
}
