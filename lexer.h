//
// Analisador lexico
//

#ifndef MINICALC_LEXER_H
#define MINICALC_LEXER_H

typedef enum tagTipoToken {
    TOKEN_INT,
    TOKEN_PRINT,
    TOKEN_ERRO,
    TOKEN_SOMA,
    TOKEN_MULT,
    TOKEN_ABREPAR,
    TOKEN_FECHAPAR,
    TOKEN_SUB,
    TOKEN_DIV,
    TOKEN_ABRECOLCH,
    TOKEN_FECHACOLCH,
    TOKEN_DECIMAL,
    TOKEN_EOF,
} TipoToken;

typedef struct tagToken {
    TipoToken tipo;
    double    valor;
} Token;


void InicializaLexer(char *arqFonte);
Token* ProximoToken();
void FinalizaLexer();


#endif //MINICALC_LEXER_H
