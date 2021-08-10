#pragma once

#include <QtCore/qglobal.h>

#if defined(IMAGE_LIBRARY)
#  define IMAGE_EXPORT Q_DECL_EXPORT
#else
#  define IMAGE_EXPORT Q_DECL_IMPORT
#endif
