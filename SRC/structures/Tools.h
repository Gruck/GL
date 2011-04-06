
#ifndef HEXALOUTRE_TOOLS_H
#define HEXALOUTRE_TOOLS_H

#define DEBUG
#define TRACE_CALLS

#include <iostream>

#ifdef DEBUG
#define DEBUG_ONLY( expr ) expr
#else
#define DEBUG_ONLY( expr )  
#endif

#ifdef TRACE_CALLS
#define CALL_MACRO std::cout << "[call] " << __PRETTY_FUNCTION__ << std::endl;
#else
#define CALL_MACRO  
#endif



#endif
