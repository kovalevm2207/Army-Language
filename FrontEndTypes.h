#ifndef FRONTENDTYPES
#define FRONTENDTYPES

typedef enum
{
    EMPTY_TOKEN,
    TOKEN_NUM,
    TOKEN_WORD
} TokenType_t;

typedef union
{
    int   num;
    char* word;
} TokenData_t;

typedef struct
{
    const char* ptr;
    TokenType_t type;
    TokenData_t data;
} Token_t;


#endif//FRONTENDTYPES
