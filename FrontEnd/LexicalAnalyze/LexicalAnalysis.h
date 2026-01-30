#ifndef ARMY_LANGUAGE_LEXICAL_ANALYSIS
#define ARMY_LANGUAGE_LEXICAL_ANALYSIS


#include "../FrontEndTypes.h"
#include "../../Instruments/Instruments.h"
#include "StackMemStruct/my_stack.h"

const int ST_LEXEME_NUM = 32;

stack_s  MakeLexicalAnalysis(char* s, const char* const file_name);
int GetNum(char** s);
char* GetWord(char** s);
Token_t IdentifyWordType(char* word);
void CompilationErrPrint(const size_t line_counter, char* const line_begining, char* const cur_pos, const char* const file_name, const char* const phrase);
long int GetInLinePos(char* const line_begining, char* const cur_pos);
void PrintErrLine(char* string, char* cur_pos);
void PrintErrUnderline(char* string, char* cur_pos);
void CleanToken(Token_t* token);

#endif//ARMY_LANGUAGE_LEXICAL_ANALYSIS
