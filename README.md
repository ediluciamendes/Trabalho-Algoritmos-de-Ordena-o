# Projeto de Ordenação de Pessoas com algoritimos de ordenação em C

Este trabalho consiste em um programa feito na linguagem C que organiza uma lista de pessoas (nome e idade) em ordem alfabética pelo nome, utilizando três algoritmos de ordenação diferentes: **Bubble Sort**, **Merge Sort** e **Quick Sort**. Além de ordenar corretamente, o programa também conta o número de comparações e trocas feitas durante a ordenação, e calcula o tempo médio de execução em milissegundos (com base em 5 execuções seguidas).

---

## Algoritmos Usados

### 🔵 Bubble Sort

O Bubble Sort é o mais simples entre os três. Ele compara os elementos vizinhos e vai trocando de posição se estiverem fora de ordem. Apesar de ser fácil de entender e implementar, não é muito eficiente em listas grandes, pois faz muitas comparações e trocas.

### 🟢 Merge Sort

O Merge Sort é baseado na ideia de dividir a lista em partes menores, ordenar cada parte separadamente e depois juntar tudo de forma ordenada. Ele é bem eficiente mesmo com muitos dados, mas usa um pouco mais de memória por causa das divisões.

### 🔴 Quick Sort

O Quick Sort também divide a lista, mas escolhe um elemento como pivô e reorganiza os outros em torno dele (menores de um lado, maiores do outro). Depois repete isso nas partes menores. É rápido na maioria dos casos, mas se escolher um pivô ruim, pode ficar mais lento.

---

## Complexidade dos Algoritmos

| Algoritmo    | Melhor Caso | Caso Médio | Pior Caso | Espaço Usado |
|--------------|-------------|------------|-----------|--------------|
| Bubble Sort  | O(n)        | O(n²)      | O(n²)     | O(1)         |
| Merge Sort   | O(n log n)  | O(n log n) | O(n log n)| O(n)         |
| Quick Sort   | O(n log n)  | O(n log n) | O(n²)     | O(log n)     |

---

## Resultados Obtidos

Foram geradas 100 pessoas aleatórias no programa. Abaixo estão os resultados médios após 5 execuções para cada algoritmo:

| Algoritmo    | Comparações | Trocas | Tempo Médio (ms) |
|--------------|-------------|--------|------------------|
| Bubble Sort  | 4950        | 2545   | 0.090            |
| Merge Sort   | 543         | 672    | 0.025            |
| Quick Sort   | 753         | 203    | 0.012            |
