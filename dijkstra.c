#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

void dijkstra(Graph* graph, int startVertex) {
    int num_vertices = graph->vertices;
    int* dist = (int*)malloc((num_vertices + 1)*sizeof(int));
    int* prev = (int*)malloc((num_vertices + 1)*sizeof(int));
    int* visited = (int*)malloc((num_vertices + 1)*sizeof(int));
    int i, j;

    for (i = 1; i <= num_vertices; i++) {
        if (graph->adjacencyMatrix[startVertex][i] != -1) {
            dist[i] = graph->adjacencyMatrix[startVertex][i];
            prev[i] = startVertex;
        }else{
            dist[i] = INT_MAX;
            prev[i] = -1;
        }
        visited[i] = 0;
    }
    visited[startVertex] = 1;
    prev[startVertex] = -1;

    // 다익스트라 알고리즘 수행
    for (i = 1; i <= num_vertices - 1; i++) {
        // 방문 안한 정점들 중 가장 작은 거리 가진 정점 찾기
        int minDist = INT_MAX;
        int u = -1;
        for (j = 1; j <= num_vertices; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        // u가 선택되었으면, 이 정점은 방문 처리
        if (u == -1) break; // 모든 정점을 방문한 경우 종료
        visited[u] = 1;

        // u와 연결된 모든 정점에 대해 거리 업데이트
        for (j = 1; j <= num_vertices; j++) {
            if (graph->adjacencyMatrix[u][j] != -1 && !visited[j]) { // 연결되어 있고 방문하지 않은 경우
                int alt = dist[u] + graph->adjacencyMatrix[u][j];
                if (alt < dist[j]) {    // 경로의 길이가 더 짧을 때만 갱신
                    dist[j] = alt;
                    prev[j] = u; // 경로 추적을 위해 이전 노드 저장
                }
            }
        }
    }
    free(visited);

    // 경로 추적
    for (i = 1; i <= num_vertices; i++) {
        if (i != startVertex && dist[i] != INT_MAX) {
            printf("정점 [%d]: ", i);
            int* path = (int*)malloc(num_vertices*sizeof(int));
            int pathIndex = 0;
            int current = i;
            while (current != -1) {
                path[pathIndex++] = current;
                current = prev[current];
            }
            for (int k = pathIndex - 1; k >= 0; k--) {
                if (k == 0){
                    printf("%d, ", path[k]);
                } else{
                    printf("%d - ", path[k]);
                }
            }
            printf("길이: %d\n", dist[i]);
            free(path);
        }
    }
    free(dist);
    free(prev);
}