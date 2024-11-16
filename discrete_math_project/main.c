#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

FILE* openFile(const char* filename, const char* mode) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("%s ������ ���µ� �����߽��ϴ�.", filename);
		exit(1);
	}
	return fp;
}

void closeFile(FILE* fp) {
	if (fp != NULL) {
		fclose(fp);
	}
}

// input1.txt ������ �д� �޼���
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

// input2.txt ������ �д� �޼���
Graph* readGraphForDijkstra(FILE* fp, int* graphNum) {
    int vertices;
    if (fscanf(fp, "%d", &vertices) != 1) {
        return NULL;  // ������ ��
    }

    Graph* graph = createGraph(vertices);
    for (int i = 1; i <= vertices; i++) {
        int vertex;
        fscanf(fp, "%d", &vertex);
        while (1) {
            int adjacent, weight;
            if (fscanf(fp, "%d %d", &adjacent, &weight) != 2) break;
            if (adjacent == 0) break;  // ���� ��
            addEdge(graph, vertex, adjacent, weight);
        }
    }
    (*graphNum)++;
    return graph;
}

// �׷��� Ž�� ��� ��� �޼���
void printTraversalResults(Graph* graph, int graphNum) {
    printf("�׷��� [%d]\n", graphNum);
    printf("----------------------------\n");

    printf("���� �켱 Ž��\n");
    DFS(graph, 1);  // �������� 1
    printf("\n");

    printf("�ʺ� �켱 Ž��\n");
    BFS(graph, 1);  // �������� 1
    printf("\n");
    printf("============================\n");
}

// �ִ� ��� ��� ���
void printDijkstraResults(Graph* graph, int graphNum) {
    printf("�׷��� [%d]\n", graphNum);
    printf("----------------------------\n");
    printf("������: 1\n");

    dijkstra(graph, 1);  // �������� 1
    printf("=========================\n");
}

int main() {
    // 1. �׷��� Ž��
    FILE* fp1 = openFile("input1.txt", "r");
    int graphNum1 = 0;
    Graph* graph;

    printf("1. �׷��� Ž�� ���� ���\n");
    while ((graph = readGraphForTraversal(fp1, &graphNum1)) != NULL) {
        printTraversalResults(graph, graphNum1);
        destroyGraph(graph);
    }
    closeFile(fp1);

    // 2. �ִ� ���
    FILE* fp2 = openFile("input2.txt", "r");
    int graphNum2 = 0;

    printf("\n2. �ִ� ��� ���ϱ� ���� ���\n");
    while ((graph = readGraphForDijkstra(fp2, &graphNum2)) != NULL) {
        printDijkstraResults(graph, graphNum2);
        destroyGraph(graph);
    }
    closeFile(fp2);

    return 0;
}
