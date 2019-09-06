#ifndef VKGRAPHIC_GLOBAL_H
#define VKGRAPHIC_GLOBAL_H


#ifdef WIN32
#if defined(VKGRAPHIC_LIBRARY)
#  define VKGRAPHICSHARED_EXPORT __declspec(dllexport)
#else
#  define VKGRAPHICSHARED_EXPORT __declspec(dllimport)
#endif
#else
#  define VKGRAPHICSHARED_EXPORT
#endif

#endif // VKGRAPHIC_GLOBAL_H
