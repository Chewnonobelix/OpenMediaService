#pragma once

#include <QtCore/qglobal.h>

#if defined(EBOOK_LIBRARY)
#  define EBOOK_EXPORT Q_DECL_EXPORT
#else
#  define EBOOK_EXPORT Q_DECL_IMPORT
#endif
