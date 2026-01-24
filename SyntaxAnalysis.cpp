#include "SyntaxAnalysis.h"

#define TOKEN_TYPE lexical_analysis.data[token].type
#define NUM_DATA   lexical_analysis.data[token].data.num
#define NAME_NUM   lexical_analysis.data[token].data.name
#define WORD_ENUM  lexical_analysis.data[token].data.word

Node_t* GetBody(const stack_s lexical_analysis, size_t* token_ptr);
Node_t* GetFunctions(const stack_s lexical_analysis, size_t* token_ptr);
Node_t* GetMain(const stack_s lexical_analysis, size_t* token_ptr);

Node_t* GetProgram(const stack_s lexical_analysis)
{
    assert(lexical_analysis.data);
    size_t token = 1;

    if(!GetStart(lexical_analysis, &token)) return NULL;

    Node_t* root = GetBody(lexical_analysis, &token);

    if(!GetEnd(lexical_analysis, &token)) DeleteTreeNode(&root);

    return root;
}
bool GetStart(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);

    size_t token = *token_ptr;

    if(TOKEN_TYPE != START_TOKEN || WORD_ENUM != ST_1) {return false;} token++;
    if(TOKEN_TYPE != START_TOKEN || WORD_ENUM != ST_2) {return false;} token++;
    if(TOKEN_TYPE != START_TOKEN || WORD_ENUM != ST_3) {return false;} token++;
    if(TOKEN_TYPE != START_TOKEN || WORD_ENUM != ST_4) {return false;} token++;

    *token_ptr = token;

    return true;
}
bool GetEnd(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);

    size_t token = *token_ptr;

    if(TOKEN_TYPE != HLT_TOKEN || WORD_ENUM != HLT_1) {return false;} token++;
    if(TOKEN_TYPE != HLT_TOKEN || WORD_ENUM != HLT_2) {return false;} token++;

    *token_ptr = token;

    return true;
}
Node_t* GetBody(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);

    Node_t* sub_func = GetFunctions(lexical_analysis, token_ptr);
    Node_t*   linker = TreeNodeCtor(OP, {.num = LINKER}, NULL, NULL);
    Node_t*     body = linker;

    while(sub_func)
    {
        TreeInsertRight(linker, sub_func);
        Node_t* new_linker = TreeNodeCtor(OP, {.num = LINKER}, NULL, NULL);
        TreeInsertLeft(linker, new_linker);
        linker = new_linker;
        new_linker = NULL;
        sub_func = GetFunctions(lexical_analysis, token_ptr);
    }

    Node_t* main_func = GetMain(lexical_analysis, token_ptr);

    if(!main_func)
    {
        fprintf(stderr, RED_COLOR "main func skipped\n" RESET);
        return body;
    }
    if(linker->prev_node)
        TreeInsertLeft(*(linker->prev_node), main_func);
    else
        body = main_func;

    //DeleteTreeNode(&linker);
    return body;
}
Node_t* GetFunctions(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);
    Node_t* func = NULL;

    size_t token = *token_ptr;
    fprintf(stderr, PURPLE_COLOR "%s: type = %s | data = %s\n" RESET, __func__, TokenTypesNames[TOKEN_TYPE], WordsTypesNames[WORD_ENUM]);
    if(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == FUNC_DEC)
    {
        fprintf(stderr, GREEN_COLOR "%s: func dec founded\n" RESET, __func__);
        token++;
        if(TOKEN_TYPE == FUNC_TOKEN     && NAME_NUM != 0)
        {
            fprintf(stderr, GREEN_COLOR "%s: sub_func founded\n" RESET, __func__);
            func = TreeNodeCtor(FUNC, {.name = NAME_NUM}, NULL, NULL);
            token++;
            *token_ptr = token;
        }
    }

    return func;
}
Node_t* GetMain(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);
    Node_t* func = NULL;

    size_t token = *token_ptr;
    fprintf(stderr, PURPLE_COLOR "%s: type = %s | data = %s\n" RESET, __func__, TokenTypesNames[TOKEN_TYPE], WordsTypesNames[WORD_ENUM]);
    if(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == FUNC_DEC)
    {
        fprintf(stderr, GREEN_COLOR "%s: func dec founded\n" RESET, __func__);
        token++;
        if(TOKEN_TYPE == FUNC_TOKEN     && NAME_NUM == 0)
        {
            fprintf(stderr, GREEN_COLOR "%s: main_func founded\n" RESET, __func__);
            func = TreeNodeCtor(FUNC, {.name = NAME_NUM}, NULL, NULL);
            token++;
        }
        *token_ptr = token;
    }

    return func;
}
