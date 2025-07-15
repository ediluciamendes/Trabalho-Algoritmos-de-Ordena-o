#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 100

typedef struct {
    char nome[100];
    int idade;
} Pessoa;

typedef struct {
    long comparacoes;
    long trocas;
} Estatisticas;

void gerarPessoas(Pessoa p[], int n) {
    char *nomes[] = {
        "Ana", "Bruno", "Carlos", "Daniela", "Eduardo", "Fernanda", "Gabriel", "Helena", "Igor", "Joana",
        "Kleber", "Larissa", "Marcos", "Natália", "Otávio", "Paula", "Renan", "Sofia", "Tiago",
        "Vinícius", "Willian", "Zeca", "Alice", "Breno", "Catarina", "Davi", "Elisa", "Felipe", "Giovana",
        "Heitor", "Isabela", "Juliano", "Karen", "Leonardo", "Milena", "Nicolas", "Olívia", "Pedro",
        "Rafaela", "Samuel", "Talita", "Ulisses", "Valentina", "Wesley", "Yasmin", "Zuleica"
    };
    int total = sizeof(nomes) / sizeof(nomes[0]);

    for (int i = 0; i < n; i++) {
        strcpy(p[i].nome, nomes[rand() % total]);
        p[i].idade = rand() % 60 + 18;
    }
}

void copiar(Pessoa origem[], Pessoa destino[], int n) {
    for (int i = 0; i < n; i++)
        destino[i] = origem[i];
}

void bubble(Pessoa p[], int n, Estatisticas *e) {
    e->comparacoes = 0;
    e->trocas = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            e->comparacoes++;
            if (strcmp(p[j].nome, p[j+1].nome) > 0) {
                Pessoa temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
                e->trocas++;
            }
        }
    }
}

void merge(Pessoa p[], int l, int m, int r, Estatisticas *e) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Pessoa *esq = malloc(n1 * sizeof(Pessoa));
    Pessoa *dir = malloc(n2 * sizeof(Pessoa));

    for (int i = 0; i < n1; i++) esq[i] = p[l + i];
    for (int j = 0; j < n2; j++) dir[j] = p[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        e->comparacoes++;
        if (strcmp(esq[i].nome, dir[j].nome) <= 0)
            p[k++] = esq[i++];
        else
            p[k++] = dir[j++];
        e->trocas++;
    }
    while (i < n1) {
        p[k++] = esq[i++];
        e->trocas++;
    }
    while (j < n2) {
        p[k++] = dir[j++];
        e->trocas++;
    }

    free(esq);
    free(dir);
}

void mergeSort(Pessoa p[], int l, int r, Estatisticas *e) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(p, l, m, e);
        mergeSort(p, m + 1, r, e);
        merge(p, l, m, r, e);
    }
}

void quick(Pessoa p[], int esq, int dir, Estatisticas *e) {
    int i = esq, j = dir;
    Pessoa piv = p[(esq + dir)/2];
    while (i <= j) {
        while ((e->comparacoes++, strcmp(p[i].nome, piv.nome) < 0)) i++;
        while ((e->comparacoes++, strcmp(p[j].nome, piv.nome) > 0)) j--;
        if (i <= j) {
            Pessoa temp = p[i];
            p[i] = p[j];
            p[j] = temp;
            e->trocas++;
            i++; j--;
        }
    }
    if (esq < j) quick(p, esq, j, e);
    if (i < dir) quick(p, i, dir, e);
}

void imprimir(Pessoa p[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s - %d\n", p[i].nome, p[i].idade);
    printf("\n");
}

void testar(char *nome, void (*alg)(Pessoa[], int, Estatisticas*), Pessoa p[], int n) {
    Pessoa temp[TAM];
    Estatisticas e;
    double total = 0;

    printf("--- %s ---\n", nome);
    for (int i = 0; i < 5; i++) {
        copiar(p, temp, n);
        clock_t ini = clock();
        alg(temp, n, &e);
        clock_t fim = clock();
        total += (fim - ini) * 1000.0 / CLOCKS_PER_SEC;
    }
    printf("Tempo médio: %.3f ms\n", total / 5);
    printf("Comparações: %ld | Trocas: %ld\n\n", e.comparacoes, e.trocas);
}

void testarMerge(Pessoa p[], int n) {
    Pessoa temp[TAM];
    Estatisticas e;
    double total = 0;

    printf("--- Merge Sort ---\n");
    for (int i = 0; i < 5; i++) {
        copiar(p, temp, n);
        e.comparacoes = e.trocas = 0;
        clock_t ini = clock();
        mergeSort(temp, 0, n-1, &e);
        clock_t fim = clock();
        total += (fim - ini) * 1000.0 / CLOCKS_PER_SEC;
    }
    printf("Tempo médio: %.3f ms\n", total / 5);
    printf("Comparações: %ld | Trocas: %ld\n\n", e.comparacoes, e.trocas);
}

void testarQuick(Pessoa p[], int n) {
    Pessoa temp[TAM];
    Estatisticas e;
    double total = 0;

    printf("--- Quick Sort ---\n");
    for (int i = 0; i < 5; i++) {
        copiar(p, temp, n);
        e.comparacoes = e.trocas = 0;
        clock_t ini = clock();
        quick(temp, 0, n-1, &e);
        clock_t fim = clock();
        total += (fim - ini) * 1000.0 / CLOCKS_PER_SEC;
    }
    printf("Tempo médio: %.3f ms\n", total / 5);
    printf("Comparações: %ld | Trocas: %ld\n\n", e.comparacoes, e.trocas);
}

int main() {
    Pessoa lista[TAM];
    srand(time(NULL));
    gerarPessoas(lista, TAM);

    printf("Primeiros nomes gerados:\n");
    imprimir(lista, 10);

    testar("Bubble Sort", bubble, lista, TAM);
    testarMerge(lista, TAM);
    testarQuick(lista, TAM);

    return 0;
}
