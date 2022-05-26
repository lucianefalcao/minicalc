// Analisador léxico para MiniCalc

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "arq.h"
#include "lexer.h"

static Buffer *buffer;
static Token *tok = NULL;

static long pos = 0;

void InicializaLexer(char *arqFonte) {
    buffer = CriaBuffer(arqFonte);

    pos = 0;

    tok = (Token*) malloc(sizeof(Token));

    if (tok == NULL) {
        fprintf(stderr, "Erro alocando memoria para o token\n");
        exit(2);
    }

    tok->tipo = TOKEN_EOF;
    tok->valor.valorInt = 0;
}

bool eof() {
    return !(pos < buffer->tam - 1);
}

char* TextoToken(long ini, long fim) {
    char *str = (char*) malloc(fim - ini + 1);

    if (str == NULL) {
        fprintf(stderr, "Erro alocando memoria\n");
        exit(1);
    }

    for (int i = 0; i + ini < fim; ++i) {
        str[i] = buffer->cont[i + ini];
    }

    str[fim - ini] = '\0';

    return str;
}

bool simbolo(char c) {
    return (c == '(' || c == ')' || c == '+' || c == '*' || c == '-' || c == '/' || c == '[' || c == ']' || c == '%' || c == '^');
}

// função: ProximoToken
//
// Dado o arquivo-fonte, obtem e retorna o próximo token
Token* ProximoToken() {
    // TODO: obtem o proximo token da entrada e preenche tok

    // pula espaços em branco
    while (!eof() && isspace(buffer->cont[pos]))
        pos++;
    
    while(!eof() && buffer->cont[pos] == '#'){
        while(pos < buffer->tam){
            ++pos;

            if(buffer->cont[pos] == '\n'){
                ++pos;
                break;
            }
        }
    }

    if (eof()) {
        tok->tipo = TOKEN_EOF;
        tok->valor.valorInt = 0;
    } else if (isalpha(buffer->cont[pos])) {
        long initPos = pos;
        while (!eof() && !isspace(buffer->cont[pos]))
            pos++;
        // texto do token: entre initPos e pos-1 no buffer
        char *texto = TextoToken(initPos, pos);
        if (strcmp(texto, "print") == 0)
        {
            tok->tipo = TOKEN_PRINT;
            tok->valor.valorInt = 0;
        } else {
            tok->tipo = TOKEN_ERRO;
            tok->valor.valorInt = 0;
        }
        free(texto);
    } else if (isdigit(buffer->cont[pos])) {
        long initPos = pos;
        bool decimal = false;
        // TODO: verificar se existe erro léxico no final do literal inteiro
        while (!eof() && (isdigit(buffer->cont[pos]) || buffer->cont[pos] == '.')) {
            if (buffer->cont[pos] == '.') {
                decimal = true;
            }
            pos++;
        }

        char *texto = TextoToken(initPos, pos);
        
        if (decimal) {
            tok->tipo = TOKEN_DECIMAL;
            sscanf(texto, "%lf", &tok->valor.valorFloat);
        } else {
            tok->tipo = TOKEN_INT;
            tok->valor.valorInt = atoi(texto);
        }

        free(texto);
    } else if (simbolo(buffer->cont[pos])) {
        switch (buffer->cont[pos]) {
            case '(':
                tok->tipo = TOKEN_ABREPAR;
                break;
            case ')':
                tok->tipo = TOKEN_FECHAPAR;
                break;
            case '+':
                tok->tipo = TOKEN_SOMA;
                break;
            case '*':
                tok->tipo = TOKEN_MULT;
                break;
            case '-':
                tok->tipo = TOKEN_SUB;
                break;
            case '/':
                tok->tipo = TOKEN_DIV;
                break;
            case '[':
                tok->tipo = TOKEN_ABRECOLCH;
                break;
            case ']':
                tok->tipo = TOKEN_FECHACOLCH;
                break;  
            case '%':
                tok->tipo = TOKEN_RESTODIV;
                break;
            case '^':
                tok->tipo = TOKEN_EXPO;
                break;   
            default:
                fprintf(stderr, "Simbolo não esperado: %c\n", buffer->cont[pos]);
        }
        tok->valor.valorInt = 0;
        pos++;
    } else {
        tok->tipo = TOKEN_ERRO;
        tok->valor.valorInt = 0;
    }

    return tok;
}

void FinalizaLexer() {
    DestroiBuffer(buffer);
    free(tok);
}
