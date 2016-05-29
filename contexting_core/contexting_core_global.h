#ifndef CONTEXTING_CORE_GLOBAL_H
#define CONTEXTING_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONTEXTING_CORE_LIBRARY)
#  define CONTEXTING_CORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONTEXTING_CORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONTEXTING_CORE_GLOBAL_H