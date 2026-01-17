#include "SyntaxAnalysis.h"

#define CUR_LEXEME_TYPE lexical_analysis.data[cur_lexeme].type
#define CUR_WORD_LEXEME lexical_analysis.data[cur_lexeme].data.word
#define CUR_NUM_LEXEME  lexical_analysis.data[cur_lexeme].data.num

#define CheckGrammar(string) CheckGrammar_(lexical_analysis, cur_lexeme, string)

#define CHECK_GRAMMAR(string)   if(!CheckGrammar(string))                                                \
                                {                                                                        \
                                    SyntaxErrPrint();                                                     \
                                    return NULL;                                                         \
                                }

#define FUNC_(func_num) TreeNodeCtor(FUNC, {.func = func_num}, NULL, NULL)
#define OP_(op_num)     TreeNodeCtor(OP,   {.op   = op_num  }, NULL, NULL)

void SyntaxErrPrint(const stack_s lexical_analysis, const size_t cur_lexeme)
{
    assert(lexical_analysis.data);
    if(CUR_LEXEME_TYPE == TOKEN_WORD)
        ERR_PRINTF("SyntaxErr: cur_lexeme: [%zu] %s\n", cur_lexeme, CUR_WORD_LEXEME);
    else if(CUR_LEXEME_TYPE == TOKEN_NUM)
        ERR_PRINTF("SyntaxErr: cur_lexeme: [%zu] %d\n", cur_lexeme, CUR_NUM_LEXEME);
    else
        ERR_PRINTF("SyntaxErr: cur_lexeme: [%zu] Unknown Lexeme Type\n", cur_lexeme);
}
Node_t* GetProgram(const stack_s lexical_analysis)
{
    assert(lexical_analysis.data);
    size_t cur_lexeme = 1;

    if(!GetStart(lexical_analysis, &cur_lexeme)) return NULL;

    // Node_t* root = GetBody(lexical_analysis, &cur_lexeme);

    if(!GetEnd(lexical_analysis, &cur_lexeme)) DeleteTreeNode(&root);

    return root;
}
Node_t* GetBody(const stack_s lexical_analysis, size_t* cur_lexeme_)
{
    assert(cur_lexeme_);
    assert(lexical_analysis.data);

    size_t cur_lexeme = *cur_lexeme_;

    Node_t* root = OP_(LINK_OP);
    Node_t* cur_linker = root;
    while(CheckGrammar("Слушай_боевую_задачу!"))
    {
        Node_t* func = GetFunctions(lexical_analysis, cur_lexeme);
        if(func)
        {
            Node_t* next_linker = OP_(LINK_OP);
            TreeInsertLeft (cur_linker, next_linker);
            TreeInsertRight(cur_linker, func);
            cur_linker = next_linker;
            continue;
        }
        break;
    }
    if(CheckGrammar("Слушай_боевую_задачу!"))
    {
        Node_t* main = NULL//GetMain(lexical_analysis, cur_lexeme);
        if(main)
        {
        TreeInsertRight(root, main);
        return root;
        }
        SyntaxErrPrint;
    }

    DeleteTreeNode(&root);
    return NULL;
}
int GetVarNum(const stack_s lexical_analysis, const size_t cur_lexeme)
{
    assert(lexical_analysis.data);

    if(CUR_LEXEME_TYPE == TOKEN_NUM)  return -1;

    int var_num = 0;
    if(CUR_LEXEME_TYPE == TOKEN_WORD)
    {
        while(var_num < VARS_NUM)
        {
            if(strcmp(CUR_WORD_LEXEME, Vars[var_num]) == 0)
                return var_num;
            var_num++;
        }
    }
    return -1;
}
int GetFuncNum(const stack_s lexical_analysis, const size_t cur_lexeme)
{
    assert(lexical_analysis.data);

    if(CUR_LEXEME_TYPE == TOKEN_NUM)  return -1;

    int func_num = 0;
    if(CUR_LEXEME_TYPE == TOKEN_WORD)
    {
        while(func_num < FUNCTIONS_NUM)
        {
            if(strcmp(CUR_WORD_LEXEME, Functions[func_num]) == 0)
                return func_num;
        }
        func_num++;
    }
    return -1;
}
bool GetStart(const stack_s lexical_analysis, size_t* cur_lexeme_)
{
    assert(cur_lexeme_);
    assert(lexical_analysis.data);

    size_t cur_lexeme = *cur_lexeme_;

    CHECK_GRAMMAR("Становись!")            cur_lexeme++;
    CHECK_GRAMMAR("Равняйсь!")             cur_lexeme++;
    CHECK_GRAMMAR("Смирно!")               cur_lexeme++;
    CHECK_GRAMMAR("Равнение_на_середину!") cur_lexeme++;

    *cur_lexeme_ = cur_lexeme;

    return true;
}
bool GetEnd(const stack_s lexical_analysis, size_t* cur_lexeme_)
{
    assert(cur_lexeme_);
    assert(lexical_analysis.data);

    size_t cur_lexeme = *cur_lexeme_;

    CHECK_GRAMMAR("Вольно!")     cur_lexeme++;
    CHECK_GRAMMAR("Разойдись!")  cur_lexeme++;

    *cur_lexeme_ = cur_lexeme;

    return true;
}
bool CheckGrammar_(const stack_s lexical_analysis, const size_t cur_lexeme, const char* const string)
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
