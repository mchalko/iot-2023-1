/**
 * @file utils.h
 * @author Mirolav Chalko
 * @brief Various utilities
 */


#ifdef USE_DPRINT
#include <stdio.h>
#define DPRINTLN(fmt, ...) printf( fmt "\n" ,##__VA_ARGS__)
#define DPRINT(fmt, ...) printf( fmt ,##__VA_ARGS__)
#else 
#define DPRINTLN(...)
#define DPRINT(...)
#endif

#define _STR(x) #x
#define STR(x) _STR(x)

