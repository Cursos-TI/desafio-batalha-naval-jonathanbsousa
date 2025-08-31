#include <stdio.h>

#define TAM 10    // tamanho do tabuleiro
#define NAVIO 3   // valor que representa navio
#define HABIL 5   // valor que representa habilidade

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Posiciona navio horizontal de tamanho fixo 3
void posicionarNavioHorizontal(int tab[TAM][TAM], int linha, int coluna) {
    for (int j = 0; j < 3; j++) {
        if (coluna + j < TAM) {
            tab[linha][coluna + j] = NAVIO;
        }
    }
}

// Posiciona navio vertical de tamanho fixo 3
void posicionarNavioVertical(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (linha + i < TAM) {
            tab[linha + i][coluna] = NAVIO;
        }
    }
}

// Posiciona navio diagonal principal (↘) de tamanho fixo 3
void posicionarNavioDiagonalPrincipal(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (linha + i < TAM && coluna + i < TAM) {
            tab[linha + i][coluna + i] = NAVIO;
        }
    }
}

// Posiciona navio diagonal secundária (↙) de tamanho fixo 3
void posicionarNavioDiagonalSecundaria(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (linha + i < TAM && coluna - i >= 0) {
            tab[linha + i][coluna - i] = NAVIO;
        }
    }
}

// Função para aplicar uma matriz de habilidade sobre o tabuleiro
void aplicarHabilidade(int tab[TAM][TAM], int hab[5][5], int centroLinha, int centroColuna) {
    int offset = 2; // como a matriz de habilidade é 5x5, o centro é em [2][2]
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (hab[i][j] == 1) {
                int linha = centroLinha + (i - offset);
                int coluna = centroColuna + (j - offset);
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                    // marca a habilidade somente se não for navio
                    if (tab[linha][coluna] == 0) {
                        tab[linha][coluna] = HABIL;
                    }
                }
            }
        }
    }
}

// Gera matriz de habilidade em cone (5x5)
void gerarCone(int hab[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                hab[i][j] = 1;
            } else {
                hab[i][j] = 0;
            }
        }
    }
}

// Gera matriz de habilidade em cruz (5x5)
void gerarCruz(int hab[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                hab[i][j] = 1;
            } else {
                hab[i][j] = 0;
            }
        }
    }
}

// Gera matriz de habilidade em octaedro (5x5 losango)
void gerarOctaedro(int hab[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                hab[i][j] = 1;
            } else {
                hab[i][j] = 0;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // posicionando navios
    posicionarNavioHorizontal(tabuleiro, 0, 0);
    posicionarNavioVertical(tabuleiro, 2, 5);
    posicionarNavioDiagonalPrincipal(tabuleiro, 5, 1);
    posicionarNavioDiagonalSecundaria(tabuleiro, 4, 8);

    printf("Tabuleiro com navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    // criando habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // aplicando habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 3, 3);
    aplicarHabilidade(tabuleiro, cruz, 7, 2);
    aplicarHabilidade(tabuleiro, octaedro, 6, 7);

    printf("Tabuleiro com habilidades aplicadas:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
