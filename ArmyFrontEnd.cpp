#include "ArmyFrontEnd.h"

int main(const int argc, const char* const argv[])
{
    char* buffer = ReadFile(argc, argv);

    stack_s lexical_analysis = MakeLexicalAnalysis(buffer);
    FREE(buffer)

    Node_t* root = GetProgram(lexical_analysis);
    StartHTMLfile();
    TreeDump(root, 0);
    DeleteTreeNode(&root);
    EndHTMLfile();
    StackDtor(&lexical_analysis);
}

stack_s  MakeLexicalAnalysis(char* s)
{
    assert(s);

    stack_s stk = {};
    StackCtor(&stk, ST_LEXEME_NUM);

    Token_t token = {};
    while(*s != '\0')
    {
        s = SkipSpaces(s);
        token.ptr = s;
        if( '0' <= *s && *s <= '9')    {token.type = TOKEN_NUM;  token.data.num  = GetNum(&s);}
        else if(is_cyrillic_symbol(s)) {token.type = TOKEN_WORD; token.data.word = GetWord(&s);}
        else
        {
            fprintf(stderr, "ERROR : [%c][%d]\n", *s, *s);
            ERR_PRINT("СЛЫШНЫХЫБЛЯ ЭТЫЧЗАХЫРНЯ БЛ!?\n");
            assert(false);
        }
        StackPush(&stk, token);
        CleanToken(&token);
        s = SkipSpaces(s);
    }

    StackDump(&stk);
    return stk;
}
