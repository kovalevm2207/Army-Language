#ifndef ARMY_LANGUAGES_INSTRUMENTS
#define ARMY_LANGUAGES_INSTRUMENTS

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <math.h>

#include "color_print.h"
#include "TreeMemStruct/Tree.h"

#ifdef DEBUG
    #define ON_DEBUG(func) func
#else
    #define ON_DEBUG(func)
#endif

#define FREE(ptr) if(ptr) {free(ptr); ptr = NULL;}
#define ERR_PRINT(text) fprintf(stderr, RED_COLOR text RESET)

const double PRECISION = 1e-12;
const size_t ST_W_LEN = 5;

const char* ReadFile(const int argc, const char* const argv[]);
char* SkipSpaces(char* ptr);
void HelpUser(void);

#endif//ARMY_LANGUAGES_INSTRUMENTS
