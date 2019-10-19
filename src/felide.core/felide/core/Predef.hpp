
#ifndef __FELIDE_PREDEF_HPP__
#define __FELIDE_PREDEF_HPP__

#if defined(FELIDE_DYNAMIC_LINK)
  #if defined(_WINDOWS)
    #error Explicit dynamic linking on Windows isn't supported yet
    #define FELIDE_API_EXPORT __declspec(dllexport)
    #define FELIDE_API_IMPORT __declspec(dllimport)
  #else
    #define FELIDE_API_EXPORT
    #define FELIDE_API_IMPORT
  #endif
#else
  #define FELIDE_API_EXPORT
  #define FELIDE_API_IMPORT  
#endif

#if defined(FELIDE_BUILD)
  #define FELIDE_API FELIDE_API_EXPORT
#else
  #define FELIDE_API FELIDE_API_IMPORT
#endif

#endif
