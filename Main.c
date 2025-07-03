#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINHAS 8
#define COLUNAS 5
#define MAX_JOGADORES 10
//Alunos: João Pedro Belineli, Thalles Allan, Caio Miranda, Guilherme Machado
// Estrutura para armazenar dados do jogador
typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

// Declaração de função
void menu(Jogador ranking[], int *numJogadores);
void jogar(Jogador ranking[], int *numJogadores);
void mostrarRegras();
void mostrarRanking(Jogador ranking[], int numJogadores);
void moverJogador(char movimento, int *x, int *y, int *pontuacao, char labirinto[LINHAS][COLUNAS]);
int venceu(int x, int y);
void atualizarRanking(Jogador ranking[], int *numJogadores, Jogador novo);

// Função principal
int main() {
    Jogador ranking[MAX_JOGADORES];
    int numJogadores = 0;
    menu(ranking, &numJogadores);
    return 0;
}

// Menu principal
void menu(Jogador ranking[], int *numJogadores) {
    int opcao;
    do {
        printf("\n=== JOGO DO LABIRINTO ===\n");
        printf("1. Jogar\n");
        printf("2. Regras\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: jogar(ranking, numJogadores); break;
            case 2: mostrarRegras(); break;
            case 3: printf("Saindo do jogo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 3);
}

// Regras do jogo
void mostrarRegras() {
    printf("\n=== REGRAS ===\n");
    printf("Objetivo: Levar o jogador da posição inicial  até o final (F).\n");
    printf("Controles:\n");
    printf("W - Cima | S - Baixo | A - Esquerda | D - Direita\n");
    printf("Você não pode atravessar paredes (#).\n");
    printf("Cada passo conta como 1 movimento, quanto menos movimentos, melhor colocação.\n");
}

// Função principal do jogo
void jogar(Jogador ranking[], int *numJogadores) {
    char labirinto[LINHAS][COLUNAS] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', '#', '#', '#', ' '},
        {' ', ' ', ' ', '#', ' '},
        {'#', '#', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#'},
        {' ', '#', '#', ' ', ' '},
        {' ', ' ', '#', '#', ' '},
        {'#', ' ', ' ', ' ', 'F'}
    };

    int x = 0, y = 0, pontuacao = 0;
    char nome[50];
    char movimento;

    printf("\nDigite seu nome: ");
    scanf(" %[^\n]", nome);

    while(!venceu(x, y)) {
        system("clear || cls"); // limpa a tela
        printf("\n=== LABIRINTO ===\n");
        for(int i = 0; i < LINHAS; i++) {
            for(int j = 0; j < COLUNAS; j++) {
                if(i == x && j == y)
                    printf("P ");
                else
                    printf("%c ", labirinto[i][j]);
            }
            printf("\n");
        }

        printf("\nMovimento (W/A/S/D): ");
        scanf(" %c", &movimento);
        moverJogador(movimento, &x, &y, &pontuacao, labirinto);
    }

    printf("\nParabéns %s! Você venceu em %d movimentos!\n", nome, pontuacao);

    Jogador novo;
    strcpy(novo.nome, nome);
    novo.pontuacao = pontuacao;

    atualizarRanking(ranking, numJogadores, novo);
    mostrarRanking(ranking, *numJogadores);
}

// Move o jogador, impedindo que passe por paredes
void moverJogador(char movimento, int *x, int *y, int *pontuacao, char labirinto[LINHAS][COLUNAS]) {
    int nx = *x, ny = *y;

    switch(movimento) {
        case 'w': case 'W': nx--; break;
        case 's': case 'S': nx++; break;
        case 'a': case 'A': ny--; break;
        case 'd': case 'D': ny++; break;
        default: printf("Movimento invalido!\n"); return;
    }

    if(nx >= 0 && nx < LINHAS && ny >= 0 && ny < COLUNAS && labirinto[nx][ny] != '#') {
        *x = nx;
        *y = ny;
        (*pontuacao)++;
    } else {
        printf("Movimento invalido ou parede!\n");
    }
}

// Verifica se o jogador venceu
int venceu(int x, int y) {
    return x == LINHAS - 1 && y == COLUNAS - 1;
}

// Atualiza o ranking
void atualizarRanking(Jogador ranking[], int *numJogadores, Jogador novo) {
    if(*numJogadores < MAX_JOGADORES) {
        ranking[*numJogadores] = novo;
        (*numJogadores)++;
    }
}

// Mostra o ranking
void mostrarRanking(Jogador ranking[], int numJogadores) {
    printf("\n=== TABELA DE JOGADORES ===\n");
    for(int i = 0; i < numJogadores; i++) {
        printf("%d. %s - %d movimentos\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }
}
