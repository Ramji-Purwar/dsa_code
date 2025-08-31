#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <string.h>

struct Node{
	int vertex;
	struct Node* next;
};

struct Graph{
	int N;
	struct Node** adjLists;
	int* visited;
};

struct Node* createNode(int ver){
	struct Node* newNode = malloc(sizeof(struct Node));
	newNode -> vertex = ver;
	newNode -> next = NULL;
	return newNode;
}

struct Graph* createGraph(int n){
	struct Graph* graph = malloc(sizeof(struct Graph));

	graph -> N = n;
	graph -> adjLists = malloc(n * sizeof(struct Node*));
	graph -> visited = malloc(n * sizeof(int));

	for(int i = 0; i < n; i++){
		graph -> adjLists[i] = NULL;
		graph -> visited[i] = 0;
	}

	return graph;
}

void createEdge(struct Graph* graph, int u, int v){
	struct Node* newNode = createNode(v);
	newNode -> next = graph -> adjLists[u];
	graph -> adjLists[u] = newNode;

	newNode = createNode(u);
	newNode -> next = graph -> adjLists[v];
	graph -> adjLists[v] = newNode;
}

void DFS(struct Graph* graph, int vertex) {
    struct Node* temp = graph->adjLists[vertex];

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	struct Graph* graph = createGraph(n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		createEdge(graph, u, v);
	}
	printf("Adjacency List:\n");
	for(int i = 0; i < graph->N; i++) {
		printf("%d: ", i);
		struct Node* temp = graph->adjLists[i];
		while(temp != NULL) {
			printf("%d ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
	DFS(graph, 0);
	printf("Visited array: ");
	for(int i = 0; i < graph->N; i++) {
		printf("%d ", graph->visited[i]);
	}
	printf("\n");
	return 0;
}