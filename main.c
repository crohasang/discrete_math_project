#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "graph.h"

FILE* openFile(const char* filename, const char* mode) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("%s 파일을 여는데 실패했습니다.", filename);
		exit(1);
	}
	return fp;
}

void closeFile(FILE* fp) {
	if (fp != NULL) {
		fclose(fp);
	}
}

// input1.txt 파일을 읽는 메서드
Graph* readGraphForTraversal(FILE* fp, int* graphNum) {
	int vertices;

	if (fscanf(fp, "%d", &vertices) != 1) {
		return NULL;
	}

	Graph* graph = createGraph(vertices, 0);

    char* line = NULL;  // 동적 메모리 포인터
    size_t len = 0;     // 버퍼 크기

    getline(&line, &len, fp);   // dummy line 패스
    for (int i = 1; i <= vertices; i++) {
        int read = getline(&line, &len, fp); // 한 줄 읽기
        if (read == -1) {
            break; // EOF
        }
        // 첫 번째 숫자는 출발 정점
        int vertex;
        char* token = strtok(line, " ");
        if (token == NULL) {
            continue; // 빈 줄 처리
        }
        vertex = atoi(token);
        // 나머지 숫자는 도착 정점
        while ((token = strtok(NULL, " ")) != NULL) {
            int adjacent = atoi(token);
            addEdge(graph, vertex, adjacent, 1); // 인접 행렬에 추가
        }
    }

    free(line); // 동적 메모리 해제
	(*graphNum)++;
	return graph;
}

// input2.txt 파일을 읽는 메서드
Graph* readGraphForDijkstra(FILE* fp, int* graphNum) {
    int vertices;
    if (fscanf(fp, "%d", &vertices) != 1) {
        return NULL;  // 파일의 끝
    }

    Graph* graph = createGraph(vertices, 1);

    char* line = NULL;  // 동적 메모리 포인터
    size_t len = 0;     // 버퍼 크기

    getline(&line, &len, fp);   // dummy line 패스
    for (int i = 1; i <= vertices; i++) {
        int read = getline(&line, &len, fp); // 한 줄 읽기
        if (read == -1) {
            break; // EOF
        }
        // 첫 번째 숫자는 출발 정점
        int vertex;
        char* token = strtok(line, " ");
        if (token == NULL) {
            continue; // 빈 줄 처리
        }
        vertex = atoi(token);
        // 나머지 숫자는 도착 정점
        while ((token = strtok(NULL, " ")) != NULL) {
            int adjacent = atoi(token);
            int weight = atoi(strtok(NULL, " "));
            addEdge(graph, vertex, adjacent, weight); // 인접 행렬에 추가
        }
    }

    free(line); // 동적 메모리 해제

    // for (int i = 1; i <= vertices; i++) {
    //     int vertex;
    //     fscanf(fp, "%d", &vertex);
    //     while (1) {
    //         int adjacent, weight;
    //         if (fscanf(fp, "%d %d", &adjacent, &weight) != 2) break;
    //         if (adjacent == 0) break;  // 줄의 끝
    //         addEdge(graph, vertex, adjacent, weight);
    //     }
    // }
    (*graphNum)++;
    return graph;
}

// 그래프 탐색 결과 출력 메서드
void printTraversalResults(Graph* graph, int graphNum) {
    printf("그래프 [%d]\n", graphNum);
    printf("----------------------------\n");

    printf("깊이 우선 탐색\n");
    DFS(graph, 1);  // 시작점은 1
    printf("\n");

    printf("너비 우선 탐색\n");
    BFS(graph, 1);  // 시작점은 1
    printf("\n");
    printf("============================\n");
}

// 최단 경로 결과 출력
void printDijkstraResults(Graph* graph, int graphNum) {
    printf("그래프 [%d]\n", graphNum);
    printf("----------------------------\n");
    printf("시작점: 1\n");

    dijkstra(graph, 1);  // 시작점은 1
    printf("=========================\n");
}

int main() {
    setlocale(LC_ALL, "Korean");

    // 1. 그래프 탐방
    FILE* fp1 = openFile("input1.txt", "r");
    int graphNum1 = 0;
    Graph* graph;

    printf("1. 그래프 탐방 수행 결과\n");
    while ((graph = readGraphForTraversal(fp1, &graphNum1)) != NULL) {
        // 그래프 임시 출력
        printf("그래프 정점 개수 : %d\n", graph->vertices);
        printf("그래프 인접 행렬\n");
        for(int i=0; i<=graph->vertices; i++){
            for(int j=0; j<=graph->vertices; j++){
                printf("%d ", graph->adjacencyMatrix[i][j]);
            }
            printf("\n");
        }
        printf("가중치 그래프 여부 : %d\n\n", graph->isWeighted);

        printTraversalResults(graph, graphNum1);
        destroyGraph(graph);
    }
    closeFile(fp1);

    // 2. 최단 경로
    FILE* fp2 = openFile("input2.txt", "r");
    int graphNum2 = 0;

    printf("\n2. 최단 경로 구하기 수행 결과\n");
    while ((graph = readGraphForDijkstra(fp2, &graphNum2)) != NULL) {
        

        printDijkstraResults(graph, graphNum2);
        destroyGraph(graph);
    }
    closeFile(fp2);

    return 0;
}
