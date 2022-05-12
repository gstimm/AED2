#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD_EDGE 1
#define LIST_GRAPH 2
#define FILL_RANDOM_GRAPH 3
#define DIJSKTRA 4
#define EXIT 5
#define FILL_TEST_VALUES 6
#define MAX_VERTICES 20
#define INFINITY 99999

void menu(int *option);
void fillInitialGraph(int graphSize);
void addWeight(int graphSize);
void listGraph(int graphSize);
void dijsktra(int graphSize);
void fillGraphWithRandomValues(int graphSize);
void fillTestValues(int graphSize);

int graph[MAX_VERTICES][MAX_VERTICES];

int main() {
  int option = 0;
  int graphSize = 0;

  while (graphSize <= 0 || graphSize > MAX_VERTICES) {
    system("clear || cls");
    printf("Quantos vértices deseja adicionar? Máx: %d\n", MAX_VERTICES);
    scanf("%d", &graphSize);
  }

  fillInitialGraph(graphSize);

  do {
    menu(&option);

    switch (option) {
    case ADD_EDGE:
      addWeight(graphSize);
      break;
    case LIST_GRAPH:
      listGraph(graphSize);
      break;
    case FILL_RANDOM_GRAPH:
      fillGraphWithRandomValues(graphSize);
      break;
    case DIJSKTRA:
      dijsktra(graphSize);
      break;
    case EXIT:
      printf("Finalizando.\n");
      exit(1);
      break;
    case FILL_TEST_VALUES:
      fillTestValues(graphSize);
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
  printf("[%d] - PREENCHER GRAFO COM VALORES ALEATÓRIOS MENORES QUE 10\n",
         FILL_RANDOM_GRAPH);
  printf("[%d] - BUSCAR MENOR CAMINHO ATRAVES DO ALGORITMO DE DIJSKTRA\n",
         DIJSKTRA);
  printf("[%d] - FINALIZAR PROGRAMA\n", EXIT);
  printf("[%d] - PREENCHER TESTE ESTÁTICO PARA DESENVOLVIMENTO\n",
         FILL_TEST_VALUES);
  printf("\nDigite a opção desejada: ");
  scanf("%d", option);
}

void fillInitialGraph(int graphSize) {
  for (int i = 0; i < graphSize; i++) {
    for (int j = 0; j < graphSize; j++) {
      graph[i][j] = 0;
    }
  }
}

void addWeight(int graphSize) {
  int verticeOne, verticeTwo, weight;
  char confirm[2];

  printf("\nADICIONAR UMA ARESTA\n\n");

  do {
    printf("Inserir vértice 1: ");
    scanf("%d", &verticeOne);

    printf("Inserir vértice 2: ");
    scanf("%d", &verticeTwo);

    verticeOne--;
    verticeTwo--;
  } while ((verticeOne < 0 || verticeOne >= graphSize) ||
           (verticeTwo < 0 || verticeTwo >= graphSize) ||
           (verticeOne == verticeTwo));

  if (graph[verticeOne][verticeTwo] == 0) {
    printf("Qual o peso da aresta?\n");
    scanf("%d", &weight);

    while (weight < 0) {
      printf("Peso inválido.\n");
      printf("Qual o peso da aresta?\n");
      scanf("%d", &weight);
    }
    graph[verticeOne][verticeTwo] = weight;
    graph[verticeTwo][verticeOne] = weight;
  } else {
    printf("Já existe uma aresta entre esses vértices, deseja alterar o "
           "valor?. Y ou N\n");
    scanf("%s", confirm);

    if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
      printf("Inserir peso:");
      scanf("%d", &weight);
      graph[verticeOne][verticeTwo] = weight;
      graph[verticeTwo][verticeOne] = weight;
    } else {
      printf("Aresta não alterada.\n");
    }
  }
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

void fillGraphWithRandomValues(int graphSize) {
  int random = 0;
  for (int i = 0; i < graphSize; i++) {
    for (int j = 0; j < graphSize; j++) {
      if (i != j) {
        random = rand() % 9 + 1;
        graph[i][j] = random;
        graph[j][i] = random;
      }
    }
  }
}

void fillTestValues(int graphSize) {
  graph[0][1] = 3;
  graph[1][0] = 3;
  graph[0][2] = 1;
  graph[2][0] = 1;
  graph[0][3] = 2;
  graph[3][0] = 2;
  graph[1][2] = 1;
  graph[2][1] = 1;
  graph[1][3] = 5;
  graph[3][1] = 5;
  graph[2][3] = 4;
  graph[3][2] = 4;
}

void dijsktra(int graphSize) {
  int distance[graphSize], visited[graphSize];
  int counter = 0, origin, destiny, shortDistance, shortDistanceIndex;

  do {
    printf("Digite o vertice de origem: ");
    scanf("%d", &origin);
  } while (origin <= 0 || origin > graphSize);

  do {
    printf("Digite o vertice de destino: ");
    scanf("%d", &destiny);
  } while (destiny <= 0 || destiny > graphSize);

  origin--;
  destiny--;
  shortDistanceIndex = origin;

  for (int i = 0; i < graphSize; i++) {
    distance[i] = INFINITY;
    visited[i] = 0;
  }

  distance[origin] = 0;
  counter++;

  while (counter < graphSize) {
    shortDistance = INFINITY;

    for (int i = 0; i < graphSize; i++) {
      if (distance[i] < shortDistance && visited[i] == 0) {
        shortDistance = distance[i];
        shortDistanceIndex = i;
      }
    }

    visited[shortDistanceIndex] = 1;

    for (int i = 0; i < graphSize; i++) {
      if (graph[shortDistanceIndex][i] != 0) {
        if (visited[i] == 0) {
          if (shortDistance + graph[shortDistanceIndex][i] < distance[i]) {
            distance[i] = shortDistance + graph[shortDistanceIndex][i];
          }
        }
      }
    }
    counter++;
  }

  if (distance[destiny] == INFINITY) {
    printf("\nNão foi possível encontrar um caminho válido.\n");
    return;
  }

  printf("\nA menor distancia entre os vertices %d e %d é: %d\n", ++origin,
         ++destiny, distance[destiny]);
}
