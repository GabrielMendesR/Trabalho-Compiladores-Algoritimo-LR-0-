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
 
## Estados
I0:  
  S' -> .S  
  S -> .AA  
  A -> .aA  
  A -> .b

I1:  
  S' -> S. (aceite)  

I2:  
  S -> A.A  
  A -> .aA  
  A -> .b

I3:  
  A -> a.A  
  A -> .aA  
  A -> .b

I4:  
  A -> b.

I5:  
  S -> AA. (reduce)

I6:  
  A -> aA. (reduce)

## Tabela de Parsing:

| Estados | Ação |       |     | GO   | TO   |
|---------|------|-------|-----|------|------|
|         | a    | b     | $   | S    | A   |
| 0       | S3   | S4    |     | 1    | 2   |
| 1       |      |       | aceita |     |     |
| 2       | S3   | S4    |     |      | 5   |
| 3       | S3   | S4    |     |      | 6   |
| 4       | r3   | r3    | r3  |      |     |
| 5       | r1   | r1    | r1  |      |     |
| 6       | r2   | r2    | r2  |      |     |

Número de estados: 7 (I0, I1, I2, ...I6)  
Produções numeradas:  
 S -> AA (1)  
 A -> aA (2) | A -> b (3)
 

 # Referências 
 - Conteúdo passado em Aula
 - Compiladores: Princípios, Técnicas e Ferramentas (Livro do Dragão)
