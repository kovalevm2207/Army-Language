#ifndef ARMY_FRONT_END
#define ARMY_FRONT_END

#include "Instruments.h"

typedef enum
{
    OP,
    NUM,
    WORD
} TokenType_t;


typedef union
{
    const char* op;
    const int   num;
    const char* word;
} TokenData_t;

typedef struct
{
    const char* ptr;
    TokenType_t type;
    TokenData_t data;
} Token_t;

const size_t ST_LEXEME_NUM = 128;

#endif//ARMY_FRONT_END
