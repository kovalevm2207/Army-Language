#ifndef ARMY_LANGUAGE_SYNTAX_ANALYSIS
#define ARMY_LANGUAGE_SYNTAX_ANALYSIS


#include "FrontEndTypes.h"
#include "Instruments.h"
#include "StackMemStruct/my_stack.h"
#include "TreeMemStruct/Tree.h"

const int ST_LEXEME_NUM = 128;

bool CheckGrammar(const stack_s lexical_analysis, const size_t cur_lexeme, const char* const string);
Node_t* GetProgram(const stack_s lexical_analysis);
bool GetStart(const stack_s lexical_analysis, size_t* cur_lexeme_);
int GetNum(char** s);
char* GetWord(char** s);

#endif//ARMY_LANGUAGE_SYNTAX_ANALYSIS
