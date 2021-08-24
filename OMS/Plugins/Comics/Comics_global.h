#pragma once

#include <QtCore/qglobal.h>

#if defined(COMICS_LIBRARY)
#  define COMICS_EXPORT Q_DECL_EXPORT
#else
#  define COMICS_EXPORT Q_DECL_IMPORT
#endif
