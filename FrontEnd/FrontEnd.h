#ifndef ARMY_FRONT_END
#define ARMY_FRONT_END

#include "FrontEndTypes.h"
#include "../Instruments/Instruments.h"
#include "LexicalAnalyze/LexicalAnalysis.h"
#include "LexicalAnalyze/StackMemStruct/my_stack.h"
#include "SyntaxAnalyze/SyntaxAnalysis.h"
#include "SyntaxAnalyze/TreeMemStruct/Tree.h"

Analyze_t ConvertToAnalyze(const stack_s lexical_analysis);

#endif//ARMY_FRONT_END
