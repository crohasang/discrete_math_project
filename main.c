#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"

FILE* openFile(const char* filename, const char* mode) {
    FILE* fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("%s 파일을 여는데 실패했습니다.\n", filename);
        exit(1);
    }
    return fp;
}

void closeFile(FILE* fp) {
    if (fp != NULL) {
        fclose(fp);
    }
}

//파일 포인터를 받아 해당 포인터로부터 첫번째의 테스트 케이스를 추출, 그래프로 변형해서 반환.
//만약 테스트 케이스가 더 없다면 NULL 반환.
Graph* readGraphFromFile(FILE* fp, int* graphNum) {
    char line[1024];
    int vertexCount = 0;

    while (1) {
        if (!fgets(line, sizeof(line), fp)) {
            return NULL;
        }
        char* ptr = line;
        while (isspace(*ptr)) ptr++;
        if (*ptr == '\0') continue;
        vertexCount = atoi(ptr);
        if (vertexCount <= 0) {
            printf("잘못된 정점 수: %s\n", ptr);
            return NULL;
        }
        break;
    }

    Graph* graph = createGraph(vertexCount);

    for (int i = 1; i <= vertexCount; i++) {
        while (1) {
            if (!fgets(line, sizeof(line), fp)) {
                destroyGraph(graph);
                return NULL;
            }
            char* ptr = line;
            while (isspace(*ptr)) ptr++;
            if (*ptr == '\0') {
                continue;
            }
            char* token = strtok(ptr, " \t\n");
            while (token != NULL) {
                int adjacent = atoi(token);
                addEdge(graph, i, adjacent, 1);
                token = strtok(NULL, " \t\n");
            }
            break;
        }
    }

    (*graphNum)++;
    return graph;
}

//유사한 방식으로 파일 포인터로부터 다익스트라에 필요한 테스트 케이스 추출, 그래프로 변환.
Graph* readGraphForDijkstra(FILE* fp, int* graphNum) {
    int vertices;
    if (fscanf(fp, "%d", &vertices) != 1) {
        return NULL;
    }

    Graph* graph = createGraph(vertices);
    if (graph == NULL) {
        printf("그래프 생성에 실패했습니다.\n");
        return NULL;
    }

    char line[1024];

    if (fgets(line, sizeof(line), fp) == NULL) {
        destroyGraph(graph);
        return NULL;
    }

    for (int i = 1; i <= vertices; i++) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("파일 형식이 올바르지 않습니다. 예상보다 적은 정점 수를 포함하고 있습니다.\n");
            destroyGraph(graph);
            return NULL;
        }
        char* ptr = line;
        while (isspace(*ptr)) ptr++;
        if (*ptr == '\0' || *ptr == '\n') {
            printf("빈 줄이 발견되었습니다. 파일 형식을 확인해주세요.\n");
            continue;
        }

        char* token = strtok(ptr, " \t\n");
        if (token == NULL) {
            printf("출발 정점 정보가 없습니다. 파일 형식을 확인해주세요.\n");
            continue;
        }

        int vertex = atoi(token);
        if (vertex <= 0 || vertex > vertices) {
            printf("잘못된 정점 번호: %d\n", vertex);
            continue;
        }

        while ((token = strtok(NULL, " \t\n")) != NULL) {
            int adjacent = atoi(token);
            token = strtok(NULL, " \t\n");
            if (token == NULL) {
                printf("가중치 정보가 누락되었습니다. 정점 %d의 간선을 확인해주세요.\n", vertex);
                break;
            }
            int weight = atoi(token);
            if (adjacent <= 0 || adjacent > vertices) {
                printf("잘못된 인접 정점 번호: %d\n", adjacent);
                continue;
            }
            if (weight < 0) {
                printf("음수 가중치는 허용되지 않습니다. 정점 %d에서 %d로의 간선 무시.\n", vertex, adjacent);
                continue;
            }
            addEdge(graph, vertex, adjacent, weight);
        }
    }

    (*graphNum)++;
    return graph;
}

//각각의 그래프에 대해서 DFS, BFS 실행, 출력 형식에 맞게 출력.
void printTraversalResults(Graph* graph, int graphNum) {
    printf("그래프 [%d]\n", graphNum);
    printf("----------------------------\n");
    printf("깊이 우선 탐색\n");
    DFS(graph, 1);
    printf("\n");
    printf("너비 우선 탐색\n");
    BFS(graph, 1);
    printf("\n");
    printf("============================\n");
}

void printDijkstraResults(Graph* graph, int graphNum) {
    printf("그래프 [%d]\n", graphNum);
    printf("----------------------------\n");
    printf("시작점: 1\n");

    dijkstra(graph, 1);
    printf("=========================\n");
}

int main() {
    FILE* fp = openFile("input1.txt", "r");
    int graphNum = 0;

    //테스트 케이스를 전부 추출해서 각각마다 printTrabersalResults 함수 호출.
    printf("1. 그래프 탐방 수행 결과\n");
    while (1) {
        Graph* graph = readGraphFromFile(fp, &graphNum);
        if (graph == NULL) {
            break;
        }

        printTraversalResults(graph, graphNum);
        destroyGraph(graph);
    }

    closeFile(fp);

    FILE* fp2 = openFile("input2.txt", "r");
    int graphNum2 = 0;
    Graph* graph;
    //유사한 방식으로 그래프 추출 후 다익스트라 결과 출력.
    printf("\n2. 최단 경로 구하기 수행 결과\n");
    while ((graph = readGraphForDijkstra(fp2, &graphNum2)) != NULL) {
        printDijkstraResults(graph, graphNum2);
        destroyGraph(graph);
    }
    closeFile(fp2);
    return 0;
}
