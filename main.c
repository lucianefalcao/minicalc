#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arq.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"

int AvaliaExpressao(Expressao *e)
{
    int res = 0;
    int v1, v2;

    switch (e->oper)
    {
    case OPER_VAR:
        if (ConsultaVar(e->nomeIdent, &v1))
        {
            res = v1;
        }
        else
        {
            fprintf(stderr, "Variavel nao declarada: %s\n", e->nomeIdent);
            exit(3);
        }
        break;
    case OPER_CONST:
        res = e->valor;
        break;
    case OPER_SOMA:
        v1 = AvaliaExpressao(e->op1);
        v2 = AvaliaExpressao(e->op2);
        res = v1 + v2;
        break;
    case OPER_MULT:
        v1 = AvaliaExpressao(e->op1);
        v2 = AvaliaExpressao(e->op2);
        res = v1 * v2;
        break;
    case OPER_SUB:
        v1 = AvaliaExpressao(e->op1);
        v2 = AvaliaExpressao(e->op2);
        res = v1 - v2;
        break;
    case OPER_DIV:
        v1 = AvaliaExpressao(e->op1);
        v2 = AvaliaExpressao(e->op2);
        res = v1 / v2;
        break;
    case OPER_RESTODIV:
        v1 = AvaliaExpressao(e->op1);
        v2 = AvaliaExpressao(e->op2);
        res = v1 % v2;
        break;
    case OPER_EXPO:
        v1 = AvaliaExpressao(e->op1);
        v2 = AvaliaExpressao(e->op2);
        res = (int)powf((float)v1, (float)v2);
        break;
    default:
        printf("Operador nao reconhecido.\n");
    }

    return res;
}

void ImprimeDeclaracoes(Declaracao *d)
{
    while (d != NULL)
    {
        printf("Declaracao - ident: %s\n", d->nomeIdent);
        d = d->next;
    }
}

void ProcessaDeclaracoes(Declaracao *d)
{
    while (d != NULL)
    {
        int val = AvaliaExpressao(d->e);
        AdicionaVar(d->nomeIdent, val);
        d = d->next;
    }
}

int main()
{
    InicializaLexer("../test/test3.mc");

    // arvore sintatica do programa
    Programa *p = AnalisePrograma();

    ProcessaDeclaracoes(p->decls);

    int resultado = AvaliaExpressao(p->e);

    printf("%d\n", resultado);

    DestroiPrograma(p);
    FinalizaLexer();
    return 0;
}
