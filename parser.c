#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "lexer.h"

Token *t;

Declaracao *AnaliseDeclaracao()
{
    t = ProximoToken();

    if (t->tipo != TOKEN_VAR)
    {
        return NULL;
    }

    Declaracao *res = (Declaracao *)malloc(sizeof(Declaracao));

    t = ProximoToken();

    if (t->tipo != TOKEN_IDENT)
    {
        fprintf(stderr, "Erro de sintaxe: identificador esperado\n");
        free(res);
        exit(2);
    }

    strcpy(res->nomeIdent, t->nome);

    t = ProximoToken();

    if (t->tipo != TOKEN_IGUAL)
    {
        fprintf(stderr, "Erro de sintaxe: '=' esperado\n");
        free(res);
        exit(2);
    }

    res->e = AnaliseExpressao();

    t = ProximoToken();

    if (t->tipo != TOKEN_PONTOVIRG)
    {
        fprintf(stderr, "Erro de sintaxe: ';' esperado no final da declaracao\n");
        free(res);
        exit(2);
    }

    return res;
}

Programa *AnalisePrograma()
{
    Programa *res = (Programa *)malloc(sizeof(Programa));

    if (res == NULL)
    {
        fprintf(stderr, "Erro de alocacao de memoria.");
        exit(1);
    }

    Declaracao *orig = AnaliseDeclaracao(); // origem da lista encadeada
    Declaracao *d = orig;
    if (d != NULL)
    {
        Declaracao *d2 = AnaliseDeclaracao();
        while (d2 != NULL)
        {
            d->next = d2;
            d = d2;
            d2 = AnaliseDeclaracao();
        }
        d->next = NULL;
    }

    res->decls = orig;

    if (t->tipo != TOKEN_PRINT)
    {
        fprintf(stderr, "Erro sintático: palavra-chave 'print' esperaca no início do programa.");
        exit(2);
    }

    res->e = AnaliseExpressao();

    return res;
}

Expressao *AnaliseExpressao()
{
    // analisa a expressao
    Expressao *res = (Expressao *)malloc(sizeof(Expressao));

    TipoToken tipoFechamentoToken;
    char tokenFechamento, tokenAbertura; // o tipo do fechamento de ser igual o de abertura, '(' ou '['.[]

    // parentese abrindo
    t = ProximoToken();

    // se proximo token for constante inteira, retorne expressao constante
    if (t->tipo == TOKEN_INT)
    {
        res->oper = OPER_CONST;
        res->valor = t->valor.valorInt;
        res->op1 = NULL;
        res->op2 = NULL;
        return res;
    }

    if (t->tipo == TOKEN_IDENT)
    {
        res->oper = OPER_VAR;
        res->valor = 0;
        strcpy(res->nomeIdent, t->nome);
        res->op1 = NULL;
        res->op2 = NULL;
        return res;
    }

    if (t->tipo == TOKEN_ABREPAR)
    {
        tipoFechamentoToken = TOKEN_FECHAPAR;
        tokenFechamento = ')';
        tokenAbertura = '(';
    }
    else if (t->tipo == TOKEN_ABRECOLCH)
    {
        tipoFechamentoToken = TOKEN_FECHACOLCH;
        tokenFechamento = ']';
        tokenAbertura = '[';
    }

    if (t->tipo != TOKEN_ABREPAR && t->tipo != TOKEN_ABRECOLCH)
    {
        fprintf(stderr, "Erro sintatico: token esperado \'%c\'\n", tokenAbertura);
        exit(2);
    }

    // primeiro operando
    res->op1 = AnaliseExpressao(); // Expressao*

    // operador
    t = ProximoToken();
    Token *a = t;

    if (t->tipo != TOKEN_SOMA && t->tipo != TOKEN_MULT && t->tipo != TOKEN_SUB && t->tipo != TOKEN_DIV && t->tipo != TOKEN_RESTODIV && t->tipo != TOKEN_EXPO)
    {
        fprintf(stderr, "Erro sintatico: operador esperado");
        exit(2);
    }

    res->oper = OPER_SUB;
    if (t->tipo == TOKEN_SOMA)
    {
        res->oper = OPER_SOMA;
    }
    else if (t->tipo == TOKEN_MULT)
    {
        res->oper = OPER_MULT;
    }
    else if (t->tipo == TOKEN_DIV)
    {
        res->oper = OPER_DIV;
    }
    else if (t->tipo == TOKEN_RESTODIV)
    {
        res->oper = OPER_RESTODIV;
    }
    else if (t->tipo == TOKEN_EXPO)
    {
        res->oper = OPER_EXPO;
    }

    // segundo operando
    res->op2 = AnaliseExpressao();

    if ((res->oper == OPER_DIV || res->oper == OPER_RESTODIV) && res->op2->valor == 0)
    {
        fprintf(stderr, "Erro matemático: divisão por zero");
        exit(2);
    }

    // parentese fechando
    t = ProximoToken();
    Token *c = t;

    if (t->tipo != tipoFechamentoToken)
    {
        fprintf(stderr, "Erro sintatico: token esperado \'%c\'\n", tokenFechamento);
        exit(1);
    }

    return res;
}

void DestroiExpressao(Expressao *e)
{
    if (e->oper == OPER_SOMA || e->oper == OPER_MULT || e->oper == OPER_SUB || e->oper == OPER_DIV || e->oper == OPER_RESTODIV || e->oper == OPER_EXPO)
    {
        DestroiExpressao(e->op1);
        DestroiExpressao(e->op2);
        e->op1 = NULL;
        e->op2 = NULL;
    }

    free(e);
}

void DestroiDeclaracoes(Declaracao *d)
{
    Declaracao *d2;
    while (d != NULL)
    {
        d2 = d->next;
        free(d);
        d = d2;
    }
}

void DestroiPrograma(Programa *p)
{
    DestroiExpressao(p->e);
    DestroiDeclaracoes(p->decls);
    p->e = NULL;
    free(p);
}