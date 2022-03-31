#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD_EDGE 1
#define LIST_GRAPH 2
#define EXIT 3
#define MAX_VERTICES 20

void menu(int *option);
void fillGraph(int graphSize);
int addWeight(int graphSize);
void listGraph(int graphSize);

int graph[MAX_VERTICES][MAX_VERTICES];

int main() {
  int option = 0;
  int graphSize = 0;

  while (graphSize <= 0 || graphSize > MAX_VERTICES) {
    system("clear || cls");
    printf("Quantos vértices deseja adicionar? Máx: %d\n", MAX_VERTICES);
    scanf("%d", &graphSize);
  }

  fillGraph(graphSize);

  do {
    menu(&option);

    switch (option) {
    case ADD_EDGE:
      addWeight(graphSize);
      break;
    case LIST_GRAPH:
      listGraph(graphSize);
      break;
    case EXIT:
      printf("Finalizando.\n");
      exit(1);
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  } while (1);

  return 0;
}

void menu(int *option) {
  printf("\nTRABALHO SOBRE GRAFOS - AED2\n");
  printf("GABRIEL SCHULTZ TIMM - 20100539\n\n");
  printf("[%d] - ADICIONAR ARESTA\n", ADD_EDGE);
  printf("[%d] - LISTAR GRAFO\n", LIST_GRAPH);
  printf("[%d] - FINALIZAR PROGRAMA\n", EXIT);
  printf("\nDigite a opção desejada: ");
  scanf("%d", option);
}

void fillGraph(int graphSize) {
  for (int i = 0; i < graphSize; i++) {
    for (int j = 0; j < graphSize; j++) {
      graph[i][j] = 0;
    }
  }
}

int addWeight(int graphSize) {
  int vertice1, vertice2, weight;
  char confirm[2];

  printf("\nADICIONAR UMA ARESTA\n\n");

  do {
    printf("Inserir vértice 1: ");
    scanf("%d", &vertice1);

    printf("Inserir vértice 2: ");
    scanf("%d", &vertice2);

    vertice1--;
    vertice2--;
  } while ((vertice1 < 0 || vertice1 >= graphSize) &&
           (vertice2 < 0 || vertice2 >= graphSize));

  if (graph[vertice1][vertice2] == 0) {
    printf("Qual o peso da aresta?\n");
    scanf("%d", &weight);

    while (weight < 0) {
      printf("Peso inválido.\n");
      printf("Qual o peso da aresta?\n");
      scanf("%d", &weight);
    }
    graph[vertice1][vertice2] = weight;
  } else {
    printf("Já existe uma aresta entre esses vértices, deseja alterar o "
           "valor?. Y ou N\n");
    scanf("%s", &confirm);

    if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
      printf("Inserir peso:");
      scanf("%d", &weight);
      graph[vertice1][vertice2] = weight;
    } else {
      printf("Aresta não alterada.\n");
    }
  }

  return graph;
}

void listGraph(int graphSize) {
  int i, j;

  printf("\nLISTAR GRAFO\n\n");

  for (i = 0; i < graphSize; i++) {
    for (j = 0; j < graphSize; j++) {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
}