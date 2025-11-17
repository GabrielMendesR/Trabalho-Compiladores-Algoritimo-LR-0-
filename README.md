# Trabalho-Compiladores-Algoritimo-LR-0-

## ALUNOS:
Gabriel Mendes Rodrigues;  
Luis Felipe Caldarelli;  
Vitor Hugo Ferreira Alves;  
Vinicius Donovan Correa Silva;  
Thiago Prado Marçal

## Especificações:
Linguagem Utilziada: C#

Algoritimo: LR(0)

Gramática Utilizada:  
S -> AA  
A -> aA | b

Palavra Utilziada: aabb

## Explicando o Algoritimo LR(0):
L - Left-to-Right: Infica a direção de leitura da entrada.  
R - Rightmost Derivation: Indica o tipo de derivação utilizada na análise sintática.  
0 - Zero Lookahead: Indica que o parser não possui lookahead, ou seja, não consegue olhar tokens à frente para tomar a próxima decisão, limitando-se assim somente ao estado atual.

Vantagem: É mais simples de implementar.  
Desvantagem: Aceita menos gramáticas devido aos conflitos a seguir.

Conflitos possiveis:  
Shift-Reduce:  
S -> α.β  
A -> α.

Reduce-Reduce:  
A -> α.  
B -> β.
 
