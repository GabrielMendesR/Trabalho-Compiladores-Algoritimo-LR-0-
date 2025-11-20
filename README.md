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
 
# Desenvolvimento

## 1. Entendendo a Gramática

Primeiro analisamos a gramática e identificamos o tipo de linguagens que ela gera pela regra (a^n b a^m b)  
### Exemplos:  
- S => AA => bA => bb (Palavra Mais Simples)
- S => AA => aAA => abA => abb
- S => AA => bA => baA => bab
- S => AA => aAA => abA => abaA => abab
- S => AA => aAA => aaAA => aabA => aabb
- S => AA => aAA => abA => abaA => abaaA => abaab

Conseguimos observar alguns padrões nas linguagens obtidas como por exemplo:
- Sempre teremos a produção exata de 2 'b'
- A palavra sempre vai terminar com 'b'

Esses padrões vão ser úteis na hora da escolha de palavras para realizar os testes no algoritimo do Parser.

A tabela de AÇÃO e GOTO foram construídas manualemnte, da mesma forma como foi realziada e corrijida em sala.  

### Tabela AÇÃO:
- SHIFT: Números Positivos ({3} -> Shift para o estado 3)
- REDUCE: Números Negativos ({-3} -> Reduce numerado de acordo com a regra de produção (3))
- ACEITE: -1
- ERRO: 0

### Tabela GOTO:
- 1: Estado 1
- 2: Estado 2
- 5: Estado 5
- 6: Estado 6
- 0: Sem Transição


 # Referências 
 - Conteúdo passado em Aula
 - Compiladores: Princípios, Técnicas e Ferramentas (Livro do Dragão)
 - Compiladores 11 - Algoritmo de Análise Sintática LR(0) - Exercício de construção da tabela LR(0) (https://www.youtube.com/watch?v=TplJNzFhOU0)
