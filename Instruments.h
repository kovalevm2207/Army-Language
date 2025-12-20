#ifndef ARMY_LANGUAGES_INSTRUMENTS
#define ARMY_LANGUAGES_INSTRUMENTS

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <math.h>
#include <cstring>

#include "FrontEndTypes.h"
#include "StackMemStruct/color_print.h"

#ifdef DEBUG
    #define ON_DEBUG(func) func
#else
    #define ON_DEBUG(func)
#endif

#define FREE(ptr) if(ptr) {free(ptr); ptr = NULL;}
#define ERR_PRINT(text) fprintf(stderr, RED_COLOR text RESET)
#define ERR_PRINTF(text, ...) fprintf(stderr, RED_COLOR text RESET, __VA_ARGS__)

const double PRECISION = 1e-12;
const size_t ST_W_LEN = 5;

char* ReadFile(const int argc, const char* const argv[]);
char* SkipSpaces(char* ptr);
void HelpUser(void);
size_t CheckLen(char** word, size_t word_len, const size_t letter);
void CleanToken(Token_t* token);
bool is_cyrillic_symbol(const char* s);
void PrintCyrillicString(char* string);

#endif//ARMY_LANGUAGES_INSTRUMENTS
