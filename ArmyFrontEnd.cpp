#include "ArmyFrontEnd.h"

int main(const int argc, const char* const argv[])
{
    const char* buffer = ReadFile(argc, argv);
    Token_t* lexical_analysis = MakeLexicalAnalysis(buffer);

    FREE(lexical_analysis)
    FREE(buffer)
}

Token_t* MakeLexicalAnalysis(const char* s)
{
    assert(s);
    *s = SkipSpaces(*s);

    Token_t* lexical_analysis = (Token_t*) calloc(ST_LEXEME_NUM);

    while(**s != '\0')
    {
        if('0' <=**s && **s <= '9')
        {

        }

    return NULL;
}
