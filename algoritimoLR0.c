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
|_Estados_|_______Ação______|____GO____|____TO____|
|_________|__a__|__b__|__$__|____S_____|____A_____|
|____0____|__S3_|__S4_|_____|____1_____|____2_____|
|____1____|_____|_____|aceit|__________|__________|
|____2____|__S3_|__S4_|_____|__________|____5_____|
|____3____|__S3_|__S4_|_____|__________|____6_____|
|____4____|__r3_|__r3_|__r3_|__________|__________|
|____5____|__r1_|__r1_|__r1_|__________|__________|
|____6____|__r2_|__r2_|__r2_|__________|__________|

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
char regras_esq[4] = {'\0', 'S', 'A', 'A'};
int regras_tam[4] = {0, 2, 2, 1};

int converter_char(char c) {
    if(c == 'a') return 0;
    if(c == 'b') return 1;
    if(c == '$') return 2;
    return -1;
}

int converter_nao_terminal(char nt) {
    if(nt == 'S') return 0;
    if(nt == 'A') return 1;
    return -1;
}

char* processar_entrada(const char* texto, int* qtde) {
    int tam = strlen(texto);
    char* tokens = malloc(tam + 2);
    int pos = 0;
    
    for(int i = 0; i < tam; i++) {
        char c = texto[i];
        if(c == 'a' || c == 'b') {
            tokens[pos++] = c;
        }
    }
    
    tokens[pos++] = '$';
    *qtde = pos;
    return tokens;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    /* Professor, colocamos o '#include <locale.h>' e o 'setlocale(LC_ALL, "Portuguese");' para conseguir fazer os prints com 'ç' e acentuação
    talvez você tenha que mudar o Encoding para o Ixo 8859-1 para exibir direito
    - CRTL+Shift+P 
    - Change File Encoding 
    - Save Witch Encoding 
    - Wetern Iso (8859-1)
    */

    char entrada[1024];
    
    printf("\nGramática:\n");
    printf("S -> AA\n");
    printf("A -> aA | b\n\n");
    printf("Digite Uma Possível Palavra(ex: aabb): ");
    
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    int num_tokens;
    char* tokens = processar_entrada(entrada, &num_tokens);
    
    if(!tokens) return 1;

    int pilha[1000], topo = 0;
    pilha[0] = 0;
    int pos = 0;
    char atual = tokens[pos];

    printf("\nPProcesso na Pilha de Parsing:\n");
    printf("Pilha\t\tEntrada\tAção\n");

    while(1) {
        int estado = pilha[topo];
        int index = converter_char(atual);
        int operacao = TABELA_ACAO[estado][index];

        printf("[");
        for(int i = 0; i <= topo; i++) {
            printf("%d", pilha[i]);
            if(i < topo) printf(" ");
        }
        printf("]\t\t");

        for(int i = pos; i < num_tokens; i++) 
            printf("%c", tokens[i]);
        printf("\t");

        if(operacao == 0) {
            printf("Erro :(\n");
            break;
        }
        if(operacao == -1) {
            printf("Aceite :)\n");
            break;
        }
        if(operacao > 0) {
            printf("Shift %d\n", operacao);
            pilha[++topo] = operacao;
            atual = tokens[++pos];
        } else {
            int regra = -operacao;
            printf("Reduce %d\n", regra);
            
            topo -= regras_tam[regra];
            int novo_estado = TABELA_GOTO[pilha[topo]][converter_nao_terminal(regras_esq[regra])];
            pilha[++topo] = novo_estado;
        }
    }

    free(tokens);
    return 0;
}