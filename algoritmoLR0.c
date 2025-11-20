/*

-- Informações e Conceitos Basicos para Começar o Desenvolvimento do Sistema --

- Iremos utilizar a mesma gramática vista em aula, portanto os estados e a tabela de Parsing serão iguais.
- Gramática, Estados, Tabela de Parsing e as Produções Númeradas para ajudar no desenvolvimento do algoritimo.
- Comentado também as variaveis e funções para ficar mais facil de entender .

Gramática:
  (0) S' -> S
  (1) S  -> A A
  (2) A  -> a A
  (3) A  -> b

--------------------------------------------------------

Estados:
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

Tabela de Parsing:
 _________________________________________________
|Estados|Ação|GO|TO_|
||a|b|$|S|_A|
|_0|S3|_S4||1|_2|
|_1|||aceit||_|
|_2|S3|_S4|||5|
|_3|S3|_S4|||6|
|_4|r3|_r3|_r3|||
|_5|r1|_r1|_r1|||
|_6|r2|_r2|_r2|||

--------------------------------------------------------

Número de estados: 7 (I0, I1, I2, ...I6)
Produções numeradas:
 S -> AA (1)
 A -> aA (2) | A -> b (3)

--------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Terminais
#define TERMINAL_A 'a'
#define TERMINAL_B 'b' 
#define TERMINAL_FIM '$'

// Nao-Terminais
#define NAO_TERMINAL_S 'S'
#define NAO_TERMINAL_A 'A'

#define TOTAL_ESTADOS 7

// Tabela AÇÃO
static const int TABELA_ACAO[TOTAL_ESTADOS][3] = {
    {  3,   4,   0 },  // a: Shift3, b: Shift4, $: erro
    {  0,   0,  -1 },  // a: erro, b: erro, $: Aceite
    {  3,   4,   0 },  // a: Shift3, b: Shift4, $: erro
    {  3,   4,   0 },  // a: Shift3, b: Shift4, $: erro
    { -3,  -3,  -3 },  // Reduce (A -> b)  (3)
    { -1,  -1,  -1 },  // Reduce (S -> AA) (1)
    { -2,  -2,  -2 }   // Reduce (A -> aA) (2)
};

// Tabela GOTO
static const int TABELA_GOTO[TOTAL_ESTADOS][2] = {
    { 1, 2 },  // S: estado 1, A: estado 2
    { 0, 0 },  // Sem Transição
    { 0, 5 },  // A: estado 5
    { 0, 6 },  // A: estado 6
    { 0, 0 },  // Sem Transição
    { 0, 0 },  // Sem Transição
    { 0, 0 }   // Sem Transição
};

// Produções da Gramática
static const char lado_esquerdo_producao[4] = { '\0', NAO_TERMINAL_S, NAO_TERMINAL_A, NAO_TERMINAL_A };
static const int tamanho_producao[4] = { 0, 2, 2, 1 };

// Terminal -> Indice Tabela Ação
int simbolo_para_indice(char simbolo) {
    switch(simbolo) {
        case 'a': return 0;
        case 'b': return 1;
        case '$': return 2;
        default: return -1;
    }
}

// Nao-terminal -> Indice Tabela GOTO
int nao_terminal_para_indice(char nao_terminal) {
    switch(nao_terminal) {
        case 'S': return 0;
        case 'A': return 1;
        default: return -1;
    }
}