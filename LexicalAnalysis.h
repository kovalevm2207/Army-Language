#ifndef ARMY_LANGUAGE_LEXICAL_ANALYSIS
#define ARMY_LANGUAGE_LEXICAL_ANALYSIS


#include "FrontEndTypes.h"
#include "Instruments.h"
#include "StackMemStruct/my_stack.h"

const int ST_LEXEME_NUM = 32;

stack_s  MakeLexicalAnalysis(char* s);
int GetNum(char** s);
char* GetWord(char** s);
Token_t IdentifyWordType(char* word);


#endif//ARMY_LANGUAGE_LEXICAL_ANALYSIS
