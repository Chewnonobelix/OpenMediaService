#include "controllerlanguage.h"

bool ControllerLanguage::setLanguageList(QStringList list)
{
    auto ret = m_language != list;

    if(ret)
        m_language = list;

    return ret;
}

QStringList ControllerLanguage::languageList() const
{
    return m_language;
}

bool ControllerLanguage::load(QString language)
{
    return m_translator.load(language, "tr");
}
