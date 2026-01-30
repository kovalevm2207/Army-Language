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

    if(!GetEnd(lexical_analysis, &token)) fprintf(stderr, "end missing\n");

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

    Node_t* body = NULL;
    Node_t* sub_func = GetFunctions(lexical_analysis, token_ptr);

    if(sub_func) body = sub_func;

    while(sub_func)
    {
        Node_t* new_sub_func = GetFunctions(lexical_analysis, token_ptr);
        TreeInsertLeft(sub_func, new_sub_func);
        if(new_sub_func) sub_func = new_sub_func;
        else break;
    }

    Node_t* main_func = GetMain(lexical_analysis, token_ptr);

    if(main_func == NULL)
    {
        fprintf(stderr, RED_COLOR "main func skipped\n" RESET);
        return body;
    }

    if(sub_func && body)
        TreeInsertLeft(sub_func, main_func);
    else if(!sub_func && !body)
        body = main_func;
    else
        fprintf(stderr, RED_COLOR "Logical err with sub_fun and body" RESET);

    return body;
}
Node_t* GetFunctions(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);

    Node_t* func = NULL;
    size_t token = *token_ptr;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == FUNC_DEC)) return func;
    token++;

    if(!(TOKEN_TYPE == FUNC_TOKEN && NAME_NUM != 0))             return func;
    func = TreeNodeCtor(FUNC, {.name = NAME_NUM}, NULL, NULL);
    token++;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == L_RND))    return func;
    Node_t* func_vars = TreeNodeCtor(OP, {.word = L_RND}, NULL, NULL);
    TreeInsertRight(func, func_vars);
    token++;

    while(TOKEN_TYPE == VAR_TOKEN)
    {
        TreeInsertRight(func_vars, TreeNodeCtor(VAR, {.name = NAME_NUM}, NULL, NULL));
        func_vars = func_vars->right;
        token++;
    }

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == R_RND))    return func;
    TreeInsertRight(func_vars, TreeNodeCtor(OP, {.word = R_RND}, NULL, NULL));
    func_vars = func_vars->right;
    token++;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == L_FIG))    return func;
    TreeInsertRight(func_vars, TreeNodeCtor(OP, {.word = L_FIG}, NULL, NULL));
    func_vars = func_vars->right;
    token++;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == R_FIG))    return func;
    TreeInsertRight(func_vars, TreeNodeCtor(OP, {.word = R_FIG}, NULL, NULL));
    token++;

    *token_ptr = token;
    return func;
}
Node_t* GetMain(const stack_s lexical_analysis, size_t* token_ptr)
{
    assert(token_ptr);
    assert(lexical_analysis.data);

    Node_t* func = NULL;
    size_t token = *token_ptr;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == FUNC_DEC)) return func;
    token++;

    if(!(TOKEN_TYPE == FUNC_TOKEN && NAME_NUM == 0))             return func;
    func = TreeNodeCtor(FUNC, {.name = NAME_NUM}, NULL, NULL);
    token++;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == L_RND))    return func;
    Node_t* func_vars = TreeNodeCtor(OP, {.word = L_RND}, NULL, NULL);
    TreeInsertRight(func, func_vars);
    token++;

    while(TOKEN_TYPE == VAR_TOKEN)
    {
        TreeInsertRight(func_vars, TreeNodeCtor(VAR, {.name = NAME_NUM}, NULL, NULL));
        func_vars = func_vars->right;
        token++;
    }

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == R_RND))    return func;
    TreeInsertRight(func_vars, TreeNodeCtor(OP, {.word = R_RND}, NULL, NULL));
    func_vars = func_vars->right;
    token++;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == L_FIG))    return func;
    TreeInsertRight(func_vars, TreeNodeCtor(OP, {.word = L_FIG}, NULL, NULL));
    func_vars = func_vars->right;
    token++;

    if(!(TOKEN_TYPE == KEY_WORD_TOKEN && WORD_ENUM == R_FIG))    return func;
    TreeInsertRight(func_vars, TreeNodeCtor(OP, {.word = R_FIG}, NULL, NULL));
    token++;

    *token_ptr = token;
    return func;
}
