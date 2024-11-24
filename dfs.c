#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void DFSUtil(Graph* graph, int* visited, int vertex) 
{
    visited[vertex] = 1;

    for (int i = 0; i < graph->vertices + 1; i++) {
        if (graph->adjacencyMatrix[vertex][i] != 0 && !visited[i]) { //인접 행렬에 1이 있고 방문한 적 없으면
            printf(" - %d", i); //노드 출력
            DFSUtil(graph, visited, i);
        }
    }
}

void DFS(Graph* graph, int startVertex) 
{
    //visited 배열 초기화
    int* visited = (int*)malloc((graph->vertices + 1) * sizeof(int));
    for (int i=0; i<graph->vertices + 1; i++)
        visited[i] = 0;

    printf("%d", startVertex); //시작점
    DFSUtil(graph, visited, startVertex); //재귀로 DFS
    
    free(visited); //메모리 free
}