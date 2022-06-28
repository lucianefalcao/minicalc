//
// Analisador lexico
//

#ifndef MINICALC_LEXER_H
#define MINICALC_LEXER_H

#define IDENT_TAM_MAX 60

#include <stdbool.h>

typedef enum tagTipoToken
{
    TOKEN_INT,
    TOKEN_PRINT,
    TOKEN_VAR,
    TOKEN_IDENT,
    TOKEN_ERRO,
    TOKEN_SOMA,
    TOKEN_MULT,
    TOKEN_ABREPAR,
    TOKEN_FECHAPAR,
    TOKEN_PONTOVIRG,
    TOKEN_IGUAL,
    TOKEN_SUB,
    TOKEN_DIV,
    TOKEN_ABRECOLCH,
    TOKEN_FECHACOLCH,
    TOKEN_DECIMAL,
    TOKEN_RESTODIV,
    TOKEN_EXPO,
    TOKEN_EOF,
} TipoToken;

typedef struct tagToken
{
    TipoToken tipo;
    union
    {
        int valorInt;
        double valorFloat;
    } valor;
    char nome[IDENT_TAM_MAX];
} Token;

void InicializaLexer(char *arqFonte);
Token *ProximoToken();
void FinalizaLexer();

#endif // MINICALC_LEXER_H
