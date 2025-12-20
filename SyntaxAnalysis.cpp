#include "SyntaxAnalysis.h"





int GetNum(char** s)
{
    assert(s);
    assert(*s);

    *s = SkipSpaces(*s);
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

    char* word = (char*) calloc(ST_W_LEN, sizeof(char));
    assert(word && "mem alloc err (calloc)");

    size_t letter = 0;
    size_t word_len = ST_W_LEN;

    *s = SkipSpaces(*s);
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
