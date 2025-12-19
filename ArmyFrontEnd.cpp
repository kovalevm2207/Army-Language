#include "ArmyFrontEnd.h"

int main(const int argc, const char* const argv[])
{
    char* buffer = ReadFile(argc, argv);
    Token_t* lexical_analysis = MakeLexicalAnalysis(buffer);

    FREE(lexical_analysis)
    FREE(buffer)
}

Token_t* MakeLexicalAnalysis(char* s)
{
    assert(s);
    s = SkipSpaces(s);

    while(*s != '\0')
    {
        if('0' <= *s && *s <= '9')
        {
            printf("тук\n");
        }
    }
    return NULL;
}
