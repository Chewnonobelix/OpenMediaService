#ifndef METADATA_H
#define METADATA_H

#include <QVariant>


class Metadata
{
private:
    QVariantMap m_metadata;
    
public:
    Metadata() = default;
    Metadata(const Metadata&) = default;
    
    QStringList metaDataList() const;
    bool hasMetadata(QString) const;
    bool hasMetadata() const;
    
    template<class T>
    T metaData(QString key) const
    {
        return m_metadata[key].value<T>();
    }
    
    template<class T>
    void setMetadata(QString key, T value)
    {
        m_metadata[key] = value;
    }
    
};

#endif // METADATA_H
