#include "LexicalAnalysis.h"

stack_s  MakeLexicalAnalysis(char* s, const char* const file_name)
{
    assert(s);

    stack_s stk = {};
    StackCtor(&stk, ST_LEXEME_NUM);

    char* line_begining = s;
    size_t line_counter = 1;
    Token_t token = {};
    while(*s != '\0')
    {
        s = SkipSpaces(s, &line_counter, &line_begining);
        if( '0' <= *s && *s <= '9')    {token.type = NUM_TOKEN;  token.data.num  = GetNum(&s);}
        else
        {
            char* cur_pos = s;
            token = IdentifyWordType(GetWord(&s));

            if(token.type == EMPTY_TOKEN)
                CompilationErrPrint(line_counter, line_begining, cur_pos, file_name, "Недопустимый символ/слово/буквенное сочетание");
        }
        StackPush(&stk, token);
        CleanToken(&token);
        s = SkipSpaces(s, &line_counter, &line_begining);
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
void CompilationErrPrint(const size_t line_counter, char* const line_begining, char* const cur_pos, const char* const file_name, const char* const phrase)
{
    assert(cur_pos);
    assert(line_begining);
    assert(file_name);
    assert(phrase);

    fprintf(stderr, "%s:%zu:%ld " RED_COLOR "error: " RESET "%s\n", file_name, line_counter, GetInLinePos(line_begining, cur_pos), phrase);
    fprintf(stderr, "%5zu |", line_counter); PrintErrLine(line_begining, cur_pos);
    fprintf(stderr, "      |"); PrintErrUnderline(line_begining, cur_pos);
}
long int GetInLinePos(char* const line_begining, char* const cur_pos)
{
    assert(cur_pos);
    assert(line_begining);

    long int in_line_pos = 0;
    for(char* counter = line_begining; counter != cur_pos; counter++)
    {
        if(is_cyrillic_symbol(counter)) counter++;
        in_line_pos++;
    }

    return in_line_pos + 1;
}
void PrintErrLine(char* string, char* cur_pos)
{
    assert(string);
    assert(cur_pos);

    bool flag = false;

    while(*string != '\0' && *string != '\n')
    {
        if(string == cur_pos)
        {
            printf(RED_COLOR);
            flag = true;
        }

        if(is_cyrillic_symbol(string))
        {
            printf("%c%c", string[0], string[1]);
            string += 2;
        }
        else
        {
            if(isspace((unsigned char) *string) && flag == true)
            {
                printf(RESET);
                flag = false;
            }

            printf("%c", *string);
            string++;
        }
    }

    printf("\n");
    return;
}
void PrintErrUnderline(char* string, char* cur_pos)
{
    assert(string);
    assert(cur_pos);

    while(*string != '\0' && *string != '\n')
    {
        if(string == cur_pos)
        {
            printf(RED_COLOR);
            while(!isspace((unsigned char) *string))
            {
                printf("^");
                is_cyrillic_symbol(string) ? string += 2 : string++;
            }
            printf(RESET);
            break;
        }
        printf(" ");
        is_cyrillic_symbol(string) ? string += 2 : string++;
    }

    printf("\n\n");
    return;
}
