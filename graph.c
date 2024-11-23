#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// 그래프 생성 및 초기화
Graph* createGraph(int vertices, int isWeighted) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;
    }
    
    graph->vertices = vertices;
    graph->isWeighted = isWeighted;
    
    // 인접 행렬 메모리 할당
    graph->adjacencyMatrix = (int**)malloc((vertices + 1) * sizeof(int*));
    if (graph->adjacencyMatrix == NULL) {
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i <= vertices; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc((vertices + 1) * sizeof(int));
        if (graph->adjacencyMatrix[i] == NULL) {
            // 이전에 할당된 메모리 해제
            for (int j = 0; j < i; j++) {
                free(graph->adjacencyMatrix[j]);
            }
            free(graph->adjacencyMatrix);
            free(graph);
            return NULL;
        }
        // 인접 행렬 초기화
        for (int j = 0; j <= vertices; j++) {
            if (i > 0 && i == j){
                graph->adjacencyMatrix[i][j] = 1;
            }
            else{
                graph->adjacencyMatrix[i][j] = 0;
            }
        }
    }
    
    return graph;
}

// 간선 추가
void addEdge(Graph* graph, int src, int dest, int weight) {
    if (!isValidVertex(graph, src) || !isValidVertex(graph, dest)) {
        return;
    }
    
    graph->adjacencyMatrix[src][dest] = weight;
    if(graph->isWeighted == 0){ // 무방향 그래프
        graph->adjacencyMatrix[dest][src] = weight;
    }
}

// 그래프 메모리 해제
void destroyGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }
    
    if (graph->adjacencyMatrix != NULL) {
        for (int i = 0; i <= graph->vertices; i++) {
            free(graph->adjacencyMatrix[i]);
        }
        free(graph->adjacencyMatrix);
    }
    
    free(graph);
}

// 인접 정점 확인
int isAdjacent(Graph* graph, int src, int dest) {
    if (!isValidVertex(graph, src) || !isValidVertex(graph, dest)) {
        return 0;
    }
    return graph->adjacencyMatrix[src][dest];
}

// 정점의 차수 계산
int getDegree(Graph* graph, int vertex) {
    if (!isValidVertex(graph, vertex)) {
        return 0;
    }
    
    int degree = 0;
    for (int i = 1; i <= graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] != 0) {
            degree++;
        }
    }
    return degree;
}

// 그래프의 정점 수 반환
int getVertexCount(Graph* graph) {
    return graph->vertices;
}

// 정점의 모든 인접 정점을 배열로 반환
void getAdjacentVertices(Graph* graph, int vertex, int* adjList, int* count) {
    *count = 0;
    
    if (!isValidVertex(graph, vertex) || adjList == NULL) {
        return;
    }
    
    for (int i = 1; i <= graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] != 0) {
            adjList[(*count)++] = i;
        }
    }
}

// 그래프 유효성 검사
int isValidVertex(Graph* graph, int vertex) {
    return (graph != NULL && vertex >= 1 && vertex <= graph->vertices);
}

// 방문 배열 생성 및 초기화
int* createVisitedArray(Graph* graph) {
    if (graph == NULL) {
        return NULL;
    }
    
    int* visited = (int*)calloc(graph->vertices + 1, sizeof(int));
    return visited;
}