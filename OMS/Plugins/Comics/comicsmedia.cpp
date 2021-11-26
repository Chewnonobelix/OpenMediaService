#include "comicsmedia.h"

ComicsMedia::ComicsMedia(MediaPointer media): m_base(media)
{
    auto p = m_base->path().split("/").last().split(".").first();

    m_extractDir = factory<QTemporaryDir>("temp/"+p);
}

QImage ComicsMedia::cover() const
{
    return QImage();
}
