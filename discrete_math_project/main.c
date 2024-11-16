#include <stdio.h>
#include <stdlib.h>
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

	Graph* graph = createGraph(vertices);
	for (int i = 1; i <= vertices; i++) {
		int vertex;
		fscanf(fp, "%d", &vertex);
		while (1) {
			int adjacent;
			if (fscanf(fp, "%d", &adjacent) != 1) break;
			if (adjacent == 0) break;
			addEdge(graph, vertex, adjacent, 1);
		}
	}
	(*graphNum)++;
	return graph;
}

// input2.txt 파일을 읽는 메서드
Graph* readGraphForDijkstra(FILE* fp, int* graphNum) {
    int vertices;
    if (fscanf(fp, "%d", &vertices) != 1) {
        return NULL;  // 파일의 끝
    }

    Graph* graph = createGraph(vertices);
    for (int i = 1; i <= vertices; i++) {
        int vertex;
        fscanf(fp, "%d", &vertex);
        while (1) {
            int adjacent, weight;
            if (fscanf(fp, "%d %d", &adjacent, &weight) != 2) break;
            if (adjacent == 0) break;  // 줄의 끝
            addEdge(graph, vertex, adjacent, weight);
        }
    }
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
    // 1. 그래프 탐방
    FILE* fp1 = openFile("input1.txt", "r");
    int graphNum1 = 0;
    Graph* graph;

    printf("1. 그래프 탐방 수행 결과\n");
    while ((graph = readGraphForTraversal(fp1, &graphNum1)) != NULL) {
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
