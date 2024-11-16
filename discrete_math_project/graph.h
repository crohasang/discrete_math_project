#ifndef GRAPH_H
#define GRAPH_H

// �׷��� ����ü ����
typedef struct {
    int vertices;           // ������ ��
    int** adjacencyMatrix; // ���� ���
    int isWeighted;        // ����ġ �׷��� ���� (0: ������ġ, 1: ����ġ)
} Graph;

// �׷��� ���� �� �ʱ�ȭ
Graph* createGraph(int vertices);

// ���� �߰� �Լ�
// src: ��� ����, dest: ���� ����, weight: ����ġ
void addEdge(Graph* graph, int src, int dest, int weight);

// �׷��� �޸� ����
void destroyGraph(Graph* graph);

// ���� ���� Ȯ�� �Լ�
// ����ġ�� �ִ� ��� ����ġ ��ȯ, ���� ��� 1 ��ȯ, ������� ���� ��� 0 ��ȯ
int isAdjacent(Graph* graph, int src, int dest);

// ������ ����(degree) ���
int getDegree(Graph* graph, int vertex);

// �׷����� ���� �� ��ȯ
int getVertexCount(Graph* graph);

// ������ ��� ���� ������ �迭�� ��ȯ
// adjList: ���� ������ ������ �迭
// count: ���� ������ ���� ������ ������
void getAdjacentVertices(Graph* graph, int vertex, int* adjList, int* count);

// �׷��� ��ȿ�� �˻�
int isValidVertex(Graph* graph, int vertex);

// �湮 �迭 ���� �� �ʱ�ȭ
int* createVisitedArray(Graph* graph);

#endif // GRAPH_H