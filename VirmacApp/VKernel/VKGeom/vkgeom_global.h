#ifndef VKGEOM_GLOBAL_H
#define VKGEOM_GLOBAL_H


#ifdef WIN32
#   if defined(VKGEOM_LIBRARY)
#       define VKGEOMSHARED_EXPORT __declspec(dllexport)
#   else
#       define VKGEOMSHARED_EXPORT __declspec(dllimport)
#   endif
#else
#   define VKGEOMSHARED_EXPORT
#endif

#endif // VKGEOM_GLOBAL_H
