#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se as posições estão livres (para qualquer tipo de navio)
int posicoesLivres(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha, c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') r += i;
        else if (direcao == 'D') { r += i; c += i; }
        else if (direcao == 'S') { r += i; c -= i; }

        // Verifica limites
        if (r < 0 || r >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO)
            return 0;

        // Verifica sobreposição
        if (tabuleiro[r][c] != 0)
            return 0;
    }
    return 1;
}

// Posiciona o navio na direção escolhida
int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    if (!posicoesLivres(tabuleiro, linha, coluna, direcao))
        return 0; // Não é possível posicionar

    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha, c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') r += i;
        else if (direcao == 'D') { r += i; c += i; }
        else if (direcao == 'S') { r += i; c -= i; }

        tabuleiro[r][c] = 3;
    }

    return 1; // Posicionamento bem-sucedido
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posicionar navios com coordenadas e direções pré-definidas
    int sucesso = 1;

    // Navio 1: Horizontal
    sucesso &= posicionarNavio(tabuleiro, 1, 2, 'H');

    // Navio 2: Vertical
    sucesso &= posicionarNavio(tabuleiro, 5, 0, 'V');

    // Navio 3: Diagonal principal ↘
    sucesso &= posicionarNavio(tabuleiro, 0, 0, 'D');

    // Navio 4: Diagonal secundária ↙
    sucesso &= posicionarNavio(tabuleiro, 0, 9, 'S');

    // Verifica se todos os navios foram posicionados
    if (!sucesso) {
        printf("Erro ao posicionar um ou mais navios.\n");
        return 1;
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
