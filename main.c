#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_matriz 7

void ler_arquivo(const char *nome_arquivo, int matriz[][tamanho_matriz]) {
    FILE *arch;
    char linha[36];  // Tamanho suficiente para armazenar a linha do arquivo
    char *token;
    int i = 0;

    arch = fopen(nome_arquivo, "r");
    if (arch == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }

    while (fgets(linha, sizeof(linha), arch)) {
        token = strtok(linha, " ");
        for (int j = 0; j < tamanho_matriz; j++) {
            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
        }
        i++;
        if (i >= tamanho_matriz) {
            break;
        }
    }

    fclose(arch);
}

int vertice_com_maior_grau(int matriz[][tamanho_matriz]) {
    int maior_grau = 0;
    int vertice_com_maior_grau = -1; // Inicializa com um valor inválido

    for (int i = 0; i < tamanho_matriz; i++) {
        int grau = 0;
        for (int j = 0; j < tamanho_matriz; j++) {
            if (matriz[i][j] != 0) { // Verifica se há uma aresta entre os vértices
                grau++;
            }
        }
        if (grau > maior_grau) {
            maior_grau = grau;
            vertice_com_maior_grau = i;
        }
    }
    return vertice_com_maior_grau;
}


void mostra_matriz(int matriz[][tamanho_matriz]) {
    printf("Matriz de adjacência:\n");
    for (int i = 0; i < tamanho_matriz; i++) {
        for (int j = 0; j < tamanho_matriz; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void escrever_graus_arquivo(char *nome_arquivo, int *graus, int tamanho)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    int i;
    for (i = 0; i < tamanho; i++)
    {
        fprintf(arquivo, "Vertice %d: Grau %d\n", i, graus[i]);
    }

    fclose(arquivo);
}

void vertices_isolados(int matriz[][tamanho_matriz]) {
    printf("Vertices isolados: \n");
     int count;
    for (int i = 0; i < tamanho_matriz; i++) {
        int isolado = 1;
        for (int j = 0; j < tamanho_matriz; j++) {
            if (matriz[i][j] != 0) { 
                isolado = 0;
                break;
            }
        }
        if (isolado) {
            printf("%d\n", i);
            count++;
        }
    }
}

void vertice_sumidouro(int matriz[][tamanho_matriz]){
    int aux = 0; // Inicializa aux com 0
    printf("Vertice(s) sumidouros:\n");
    for(int cont = 0; cont < tamanho_matriz; cont++){
        int sumidouro = 1;
        for(int cont2 = 0; cont2 < tamanho_matriz; cont2++){
            if (matriz[cont][cont2] != 0){
                sumidouro = 0;
                break;
            }
        } 
        if(sumidouro){
            printf("%d\n", cont);
            aux++;
        }
    }
    if (aux == 0){ // Se aux ainda for 0, nenhum vértice sumidouro foi encontrado
        printf("Nao foi encontrado vertice sumidouro!\n");
    }
}

int main() {
    int i;
    int matriz_adjacencia[tamanho_matriz][tamanho_matriz];
    ler_arquivo("matriz.txt", matriz_adjacencia);
    mostra_matriz(matriz_adjacencia);

    int maior_grau = vertice_com_maior_grau(matriz_adjacencia);
    printf("vertice com maior grau do grafo: %d\n", maior_grau);

    int *graus = (int *)malloc(tamanho_matriz * sizeof(int));
    for (i = 0; i < tamanho_matriz; i++)
        graus[i] = 0;

    for (i = 0; i < tamanho_matriz; i++)
    {
        int j;
        for (j = 0; j < tamanho_matriz; j++)
        {
            if (matriz_adjacencia[i][j] == 1)
                graus[i]++;
        }
    }

    escrever_graus_arquivo("dados_grafos_graus.txt", graus, tamanho_matriz);
    vertices_isolados(matriz_adjacencia);
    vertice_sumidouro(matriz_adjacencia);
    return 0;
}
