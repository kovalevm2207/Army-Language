#ifndef ARMY_LANGUAGE_SYNTAX_ANALYSIS
#define ARMY_LANGUAGE_SYNTAX_ANALYSIS

#include "../FrontEndTypes.h"
#include "../../Instruments/Instruments.h"
#include "TreeMemStruct/Tree.h"

typedef struct
{
    Token_t* data;
    size_t size;
    size_t capacity;
    int STATUS;
} Analyze_t;

#define TOKEN_TYPE lexical_analysis.data[token].type
#define NUM_DATA   lexical_analysis.data[token].data.num
#define NAME_NUM   lexical_analysis.data[token].data.name
#define WORD_ENUM  lexical_analysis.data[token].data.word

Node_t* GetProgram(const Analyze_t lexical_analysis);
bool GetStart(const Analyze_t lexical_analysis, size_t* token_ptr);
bool GetEnd(const Analyze_t lexical_analysis, size_t* token_ptr);
Node_t* GetBody(const Analyze_t lexical_analysis, size_t* token_ptr);
Node_t* GetFunctions(const Analyze_t lexical_analysis, size_t* token_ptr);
Node_t* GetMain(const Analyze_t lexical_analysis, size_t* token_ptr);
Node_t* GetDescription(const Analyze_t lexical_analysis, size_t* token_ptr);
Node_t* GetVarDeclaration(const Analyze_t lexical_analysis, size_t* token_ptr);

#endif//ARMY_LANGUAGE_SYNTAX_ANALYSIS
