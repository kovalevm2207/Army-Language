#include "LexicalAnalysis.h"

stack_s  MakeLexicalAnalysis(char* s)
{
    assert(s);

    stack_s stk = {};
    StackCtor(&stk, ST_LEXEME_NUM);

    Token_t token = {};
    while(*s != '\0')
    {
        s = SkipSpaces(s);
        if( '0' <= *s && *s <= '9')    {token.type = NUM_TOKEN;  token.data.num  = GetNum(&s);}
        else
        {
            token = IdentifyWordType(GetWord(&s));
            if(token.type == EMPTY_TOKEN)
            {
                ERR_PRINTF("ERROR : [%c][%d]\n", *s, *s);
                ERR_PRINT ("СЛЫШНЫХЫБЛЯ ЭТЫЧЗАХЫРНЯ БЛ!?\n");
                assert(false);
            }
        }
        StackPush(&stk, token);
        CleanToken(&token);
        s = SkipSpaces(s);
    }

    StackDump(&stk);
    return stk;
}
int GetNum(char** s)
{
    assert(s);
    assert(*s);

    int sign = 1;

    if(**s == '-')
    {
        sign = -1;
        ++*s;
    }

    if(!('0' <= **s && **s <= '9'))
    {
        ERR_PRINT("SyntaxErr in GetN\n");
        return 0;
    }

    int val = 0;
    while('0'<= **s && **s <= '9')
    {
        val = val*10 + **s - '0';
        ++*s;
    }

    return val * sign;
}
char* GetWord(char** s)
{
    assert(s);
    assert(*s);

    if(!is_cyrillic_symbol(*s)) return NULL;

    char* word = (char*) calloc(ST_W_LEN, sizeof(char));
    assert(word && "mem alloc err (calloc)");

    size_t letter = 0;
    size_t word_len = ST_W_LEN;

    while(is_cyrillic_symbol(*s) || **s == '_' || **s == '!' || **s == '?')
    {
        if(is_cyrillic_symbol(*s))
        {
            word[letter++] = (*s)[0];
            word_len = CheckLen(&word, word_len, letter);
            word[letter++] = (*s)[1];
            (*s) += 2;
        }
        else
        {
            word[letter++] = **s;
            ++*s;
        }

        word_len = CheckLen(&word, word_len, letter);
        assert(word_len);
    }
    if(letter == 0) {FREE(word); return NULL;}
    word[letter] = '\0';

    return word;
}
Token_t IdentifyWordType(char* word)
{
    Token_t ret_val = {EMPTY_TOKEN, UNKNOWN};
    if(!word) return ret_val;

    for(size_t cur_arr = 0; cur_arr < NOT_NAME_ARROWS_NUM; cur_arr++)
    {
        for(size_t i = 0; i < NotNameArrows[cur_arr].len; i++)
        {
            if(strcmp(word, NotNameArrows[cur_arr].arrow[i].name) == 0)
            {
                ret_val.type      = NotNameArrows[cur_arr].type;
                ret_val.data.word = NotNameArrows[cur_arr].arrow[i].num;
                FREE(word)
                return ret_val;
            }
        }
    }

    for(size_t i = 0; i < VARS_NUM; i++)
    {
        if(strcmp(word, Vars[i]) == 0)
        {
            ret_val.type = VAR_TOKEN;
            ret_val.data.name = i;
            FREE(word)
            return ret_val;
        }
    }
    for(size_t i = 0; i < FUNCTIONS_NUM; i++)
    {
        if(strcmp(word, Functions[i]) == 0)
        {
            ret_val.type = FUNC_TOKEN;
            ret_val.data.name = i;
            FREE(word)
            return ret_val;
        }
    }

    FREE(word)
    return ret_val;
}
