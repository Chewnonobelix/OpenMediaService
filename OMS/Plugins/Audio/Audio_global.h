#pragma once

#include <QtCore/qglobal.h>

#if defined(AUDIO_LIBRARY)
#  define AUDIO_EXPORT Q_DECL_EXPORT
#else
#  define AUDIO_EXPORT Q_DECL_IMPORT
#endif
