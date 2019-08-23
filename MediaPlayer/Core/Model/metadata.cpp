#include "metadata.h"


QStringList Metadata::metaDataList() const
{
    return m_metadata.keys();
}

bool Metadata::hasMetadata(QString key) const
{
    return m_metadata.contains(key);
}

bool Metadata::hasMetadata() const
{
    return !m_metadata.empty();
}



