#include "SyntaxAnalysis.h"

#define CHECK_GRAMMAR(cur_lexeme, string)   if(!CheckGrammar(lexical_analysis, cur_lexeme, string))                \
                                            {                                                                      \
                                                if(lexical_analysis.data[cur_lexeme].type == TOKEN_WORD)           \
                                                {                                                                  \
                                                    ERR_PRINTF("SyntaxErr: cur_lexeme: [%zu] %s",                  \
                                                    cur_lexeme, lexical_analysis.data[cur_lexeme].data.word);      \
                                                }                                                                  \
                                                else if(lexical_analysis.data[cur_lexeme].type == TOKEN_NUM)       \
                                                {                                                                  \
                                                    ERR_PRINTF("SyntaxErr: cur_lexeme: [%zu] %d",                  \
                                                    cur_lexeme, lexical_analysis.data[cur_lexeme].data.num);       \
                                                }                                                                  \
                                                else                                                               \
                                                {                                                                  \
                                                    ERR_PRINTF("SyntaxErr: cur_lexeme: [%zu] Unknown Lexeme Type", \
                                                    cur_lexeme);                                                   \
                                                }                                                                  \
                                                return NULL;                                                       \
                                            }

Node_t* GetProgram(const stack_s lexical_analysis)
{
    assert(lexical_analysis.data);

    size_t cur_lexeme = 1;
    if(!GetStart(lexical_analysis, &cur_lexeme)) return NULL;

    return TreeNodeCtor(VAR, {.var = 5}, NULL, NULL);
}

bool GetStart(const stack_s lexical_analysis, size_t* cur_lexeme_)
{
    assert(cur_lexeme_);
    assert(lexical_analysis.data);

    size_t cur_lexeme = *cur_lexeme_;

    CHECK_GRAMMAR(cur_lexeme, "Становись!"); cur_lexeme++;
    CHECK_GRAMMAR(cur_lexeme, "Равняйсь!");  cur_lexeme++;
    CHECK_GRAMMAR(cur_lexeme, "Смирно!");    cur_lexeme++;

    *cur_lexeme_ = cur_lexeme;

    return true;
}
bool CheckGrammar(const stack_s lexical_analysis, const size_t cur_lexeme, const char* const string)
{
    assert(string);
    assert(lexical_analysis.data);
    assert(cur_lexeme <= lexical_analysis.capacity);

    if(lexical_analysis.data[cur_lexeme].type != TOKEN_WORD) return false;
        // Можно было бы и внести все в одну строчку, но мб будет Udefine Behaver когда попадется число
    return strcmp(lexical_analysis.data[cur_lexeme].data.word, string) == 0;
}
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
