#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "lexer.h"

Token *t;

Programa *AnalisePrograma()
{
    Programa *res = (Programa *)malloc(sizeof(Programa));

    if (res == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria.");
        exit(1);
    }

    // verifica se o programa começa com palavra-chave 'print'
    t = ProximoToken();

    if (t->tipo != TOKEN_PRINT)
    {
        fprintf(stderr, "Erro sintático: palavra-chave 'print' esperaca no início do programa.");
        exit(2);
    }

    res->e = AnaliseExpressao();

    //    t = ProximoToken();
    //
    //    if (t->tipo != TOKEN_EOF) {
    //        fprintf(stderr, "Erro sintatico: entrada adicional apos fim do programa.");
    //        exit(2);
    //    }

    return res;
}

Expressao *AnaliseExpressao()
{
    // analisa a expressao
    Expressao *res = (Expressao *)malloc(sizeof(Expressao));

    // parentese abrindo
    t = ProximoToken();
    Token *b = t;

    // se proximo token for constante inteira, retorne expressao constante
    if (t->tipo == TOKEN_INT)
    {
        res->oper = OPER_CONST;
        res->valor = t->valor.valorInt;
        res->op1 = NULL;
        res->op2 = NULL;
        return res;
    }

    if (t->tipo != TOKEN_ABREPAR)
    {
        fprintf(stderr, "Erro sintatico: '(' esperado");
        exit(2);
    }

    // primeiro operando
    res->op1 = AnaliseExpressao(); // Expressao*

    // operador
    t = ProximoToken();
    Token *a = t;

    if (t->tipo != TOKEN_SOMA && t->tipo != TOKEN_MULT)
    {
        fprintf(stderr, "Erro sintatico: operador esperado");
        exit(2);
    }

    res->oper = (t->tipo == TOKEN_SOMA ? OPER_SOMA : OPER_MULT);

    // segundo operando
    res->op2 = AnaliseExpressao();

    // parentese fechando
    t = ProximoToken();
    Token *c = t;

    if (t->tipo != TOKEN_FECHAPAR)
    {
        fprintf(stderr, "Erro sintatico: ')' esperado");
        exit(2);
    }

    return res;
}

void DestroiExpressao(Expressao *e)
{
    if (e->oper == OPER_SOMA || e->oper == OPER_MULT)
    {
        DestroiExpressao(e->op1);
        DestroiExpressao(e->op2);
        e->op1 = NULL;
        e->op2 = NULL;
    }

    free(e);
}

void DestroiPrograma(Programa *p)
{
    DestroiExpressao(p->e);
    p->e = NULL;
    free(p);
}