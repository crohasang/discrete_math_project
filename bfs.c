#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void BFS(Graph* graph, int startVertex) {
    if (!isValidVertex(graph, startVertex)) {
        printf("유효하지 않은 시작 정점입니다.\n");
        return;
    }

    // 방문 배열 생성 및 초기화
    int* visited = createVisitedArray(graph);

    // 큐 생성
    int* queue = (int*)malloc((graph->vertices + 1) * sizeof(int));
    if (queue == NULL) {
        printf("큐 메모리 할당 실패\n");
        return;
    }
    int front = 0, rear = 0;

    // 시작 정점을 방문 처리하고 큐에 추가
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS 탐색 순서: ");

    while (front < rear) {
        // 큐에서 정점 제거
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // 현재 정점의 모든 인접 정점 탐색
        for (int i = 1; i <= graph->vertices; i++) {
            if (graph->adjacencyMatrix[currentVertex][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");

    // 메모리 해제
    free(visited);
    free(queue);
}
