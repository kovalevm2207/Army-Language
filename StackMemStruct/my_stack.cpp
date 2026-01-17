#include "my_stack.h"

StackErr_t StackCtor_(stack_s* stk, size_t capacity, const char* file, int line)
{
    int STATUS = ALL_OK;
    START_OK // todo better make new function

    stk->data = (stack_t*) calloc(capacity  + 2, sizeof(stack_t));
    stk->size = 1;
    stk->capacity = capacity;
    stk->data[0].data.num = L_STACK_CANARY;
    stk->data[0].type     = EMPTY_TOKEN;
    stk->data[capacity + 1].data.num = R_STACK_CANARY;
    for (size_t i = 1; i < capacity + 1; i++)
    {
        stk->data[i].data.num = STACK_POISON;
        stk->data[i].type = EMPTY_TOKEN;
    }

    STACK_OK

    return ALL_OK;
}
StackErr_t StackPush_(stack_s* stk, stack_t value, const char* file, int line)
{
    int STATUS = ALL_OK;
    STACK_OK

    size_t capacity = stk->capacity;
    if (stk->size > capacity)
    {
        stack_t* new_data = (stack_t*) realloc(stk->data, (capacity * 2 + 2) * sizeof(stack_t));
        if (new_data == NULL) {printf(RED_COLOR "MEMORY ALLOCATION ERR\n" RESET); return STACK_REALLOC_ERR;}

        stk->data = new_data;
        for(size_t i = 1; i <= capacity; i++)
        {
            new_data[capacity + i].data.num = STACK_POISON;
            new_data[capacity + i].type     = EMPTY_TOKEN;
        }
        stk->capacity *= 2;
        stk->data[stk->capacity + 1].data.num = R_STACK_CANARY;
    }

    stk->data[stk->size] = value;
    stk->size++;

    STACK_OK

    return ALL_OK;
}
StackErr_t StackPop_(stack_s* stk, stack_t* value, const char* file, int line)
{
    int STATUS = ALL_OK;
    if (value == NULL) STATUS |= BAD_VALUE;
    STACK_OK

    stk->size--;
    *value = stk->data[stk->size];
    stk->data[stk->size].data.num = STACK_POISON;

    STACK_OK

    return ALL_OK;
}
StackErr_t StackDtor_(stack_s* stk, const char* file, int line)
{
    int STATUS = ALL_OK;
    STACK_OK

    for(size_t i = 1; i <= stk->capacity; i++)
    {
        if(stk->data[i].type == TOKEN_WORD)
            FREE(stk->data[i].data.word)

        stk->data[i].data.num = STACK_POISON;
        stk->data[i].type     = EMPTY_TOKEN;
    }

    FREE(stk->data);
    stk->size = 0;
    stk->capacity = 0;
    stk = NULL;

    return ALL_OK;
}
StackErr_t StackVerify(stack_s* stk, int STATUS) // todo add poisons
{
    if (stk == NULL) {
       STATUS |= BAD_STK_PTR;
       return (StackErr_t) STATUS;
    }
    if (stk->capacity > MAXSIZE)                  STATUS |= BAD_STK_CAPACITY;
    if (stk->size > stk->capacity + 1)            STATUS |= BAD_SIZE_R;
    if (stk->size < 1)                            STATUS |= BAD_SIZE_L;
    if (stk->data == NULL)                        STATUS |= BAD_DATA_PTR;
    else {
        if (stk->data[0].data.num != L_STACK_CANARY)                 STATUS |= LEFT_CANARY_DEAD;
        if (stk->data[stk->capacity + 1].data.num != R_STACK_CANARY) STATUS |= RIGHT_CANARY_DEAD;
    }
    return (StackErr_t) STATUS;
}
StackErr_t StackDump(stack_s* stk)
{
    if (stk == NULL)                    {printf("BAD_STK_PTR\n"); return BAD_STK_PTR;}

    int STATUS = stk->STATUS;

    printf("stack " CHANGE_ON GREEN TEXT_COLOR "<int>" CHANGE_ON BLUE TEXT_COLOR
           "       [0x%lx]" RESET " ____________________________ ", (uintptr_t)stk);
    if (STATUS == ALL_OK) printf(CHANGE_ON BOLD WITH GREEN TEXT_COLOR "ALL_OK(%d) " RESET, ALL_OK);
    else printf(CHANGE_ON RED TEXT_COLOR "ERROR! ");

    if (STATUS & BAD_VALUE)              printf("BAD_VALUE(%d) ",    BAD_VALUE);
    if (STATUS & BAD_START_CAPACITY)     printf("BAD_START_CAPACITY(%d) ",    BAD_START_CAPACITY);
    if (STATUS & BAD_SIZE_R)             printf("BAD_SIZE_RIGHT(%d) ", BAD_SIZE_R);
    if (STATUS & BAD_SIZE_L)             printf("BAD_SIZE_LEFT(%d) ", BAD_SIZE_L);
    if (STATUS & BAD_STK_CAPACITY)       printf("BAD_STK_CAPACITY(%d) ", BAD_STK_CAPACITY);
    if (STATUS & BAD_DATA_PTR)           printf("BAD_DATA_PTR(%d) ", BAD_DATA_PTR);
    if (STATUS & LEFT_CANARY_DEAD)       printf("LEFT_CANARY_DEAD(%d) ", LEFT_CANARY_DEAD);
    if (STATUS & RIGHT_CANARY_DEAD)      printf("RIGHT_CANARY_DEAD(%d) ", RIGHT_CANARY_DEAD);

    printf(RESET "\n");

    stk->STATUS |= print_data(stk);
    if (stk->STATUS & BAD_PRINT_DATA) return BAD_PRINT_DATA;

    return ALL_OK;
}
StackErr_t print_data(stack_s* stk)
{
    if (stk == NULL) {
        printf(RED_COLOR "BAD_PRINT_DATA(%d) " RESET, BAD_PRINT_DATA);
        return BAD_PRINT_DATA;
    }

        int STATUS = stk->STATUS;

    printf(RESET "\n");
        printf("{\n");
        printf(GREEN_COLOR "    size       " BLUE_COLOR  "%zu"     RESET "\n", stk->size - 1);
        printf(GREEN_COLOR "    capacity   " BLUE_COLOR  "%zu"     RESET "\n", stk->capacity);
        printf(GREEN_COLOR "    data       " BLUE_COLOR  "[0x%lx]" RESET "\n", (uintptr_t)stk->data);
    if (!(STATUS & BAD_DATA_PTR || STATUS & BAD_STK_CAPACITY || STATUS & BAD_START_CAPACITY)) {
        printf("    {\n");
        for (size_t i = 0; i < stk->capacity + 2; i++) {
            if (stk->data[i].data.num == STACK_POISON)
                printf(CYAN_COLOR  "        [%4zu] = %d         (POISON)\n" RESET, i, stk->data[i].data.num);
            if (stk->data[i].data.num == L_STACK_CANARY || stk->data[i].data.num == R_STACK_CANARY)
                printf(PURPLE_COLOR "        [%4zu] = %d         (CANARY)\n" RESET, i, stk->data[i].data.num);
            else if (stk->data[i].data.num != STACK_POISON )
            {
                if(stk->data[i].type == TOKEN_NUM)
                    printf(ORANGE_COLOR "       *[%4zu] = %d\n" RESET, i, stk->data[i].data.num);
                else
                {
                    printf(ORANGE_COLOR "       *[%4zu] = ", i);
                    PrintCyrillicString(stk->data[i].data.word);
                    printf(             "\n" RESET);
                }
            }
        }
    printf("    }\n\n");
    }
    printf("}\n");

    return ALL_OK;
}
