
#ifndef HEXALOUTRE_TOOLS_H
#define HEXALOUTRE_TOOLS_H

#define DEBUG
#define TRACE_CALLS

#include <iostream>

/*
 * Macro permettant de générer des portions de code uniquement lorsque la cible
 * de compilation est DEBUG
 *
 * exemple: DEBUG_ONLY( std::cout << "foo\n"; )
 * l'instruction std::cout << foo n'est générée que si #define DEBUG 
 */ 
#ifdef DEBUG
#define DEBUG_ONLY( expr ) expr
#else
#define DEBUG_ONLY( expr )  
#endif

/*
 * Macro générant un affichage de la function courante dans la sortie standard.
 *
 * Utile pour visualiser rapidement la stack-trace.
 * Aucun code n'est généré si la macro TRACE_CALLS n'est pas définie 
 */ 
#ifdef TRACE_CALLS
#define CALL_MACRO std::cout << "[call] " << __PRETTY_FUNCTION__ << std::endl;
#else
#define CALL_MACRO  
#endif



#endif
