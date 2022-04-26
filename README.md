MiniCalc
========

Uma linguagem simples para cálculo de expressões aritméticas.
O interpretador para a linguagem será desenvolvido em estágios, começando
com a versão mais simples e gradativamente adicionando novos
recursos.

## Estágio 1

Programas são da forma

```
print E
```

sendo E uma expressão. As expressões podem ser:

```
E ::= (E + E) | (E * E) 
E ::= <numero>
```

`<numero>` é um número inteiro.

Exemplo 1:
```
print 2
```

Exemplo 2:
```
print (4 + 5)
```

Exemplo 3:
```
print (4 + (2 * 3))
```

### Atividades

- [x] Adicione suporte no analisador léxico para operador de subtração, -
- [x] Adicione suporte no analisador léxico para operador de divisão, /
- [x] Adicione suporte no analisador léxico para colchetes []
- [ ] O que acontece, no código atual, se o arquivo-fonte contiver uma constante
numérica com ponto decimal? Faça o teste executando o programa, mostre a saída
obtida e explique o que está acontecendo.
- [ ] **Opcional**: adicione suporte no analisador léxico para reconhecer constantes
numéricas com ponto decimal
- [ ] **Opcional**: adicione suporte a comentários no código-fonte. Comentários não geram
token, devem apenas ser pulados como se fossem espaço em branco. Comentários
devem começar com # e continuam até o final da linha. Após encontrar #, o
analisador léxico deve ignorar todos os caracteres até encontrar um caractere de
final de linha (\n).
