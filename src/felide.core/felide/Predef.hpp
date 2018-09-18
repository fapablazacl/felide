
#ifndef __FELIDE_PREDEF_HPP__
#define __FELIDE_PREDEF_HPP__

#define FELIDE_API_EXPORT 
#define FELIDE_API_IMPORT 

#if defined(FELIDE_BUILD)
#define FELIDE_API FELIDE_API_EXPORT
#else
#define FELIDE_API FELIDE_API_IMPORT
#endif

#endif
