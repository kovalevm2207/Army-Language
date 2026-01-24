#ifndef ARMY_LANGUAGE_SYNTAX_ANALYSIS
#define ARMY_LANGUAGE_SYNTAX_ANALYSIS

#include "FrontEndTypes.h"
#include "Instruments.h"
#include "StackMemStruct/my_stack.h"
#include "TreeMemStruct/Tree.h"

Node_t* GetProgram(const stack_s lexical_analysis);
bool GetStart(const stack_s lexical_analysis, size_t* token_ptr);
bool GetEnd(const stack_s lexical_analysis, size_t* token_ptr);

#endif//ARMY_LANGUAGE_SYNTAX_ANALYSIS
