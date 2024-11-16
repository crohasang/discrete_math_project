#ifndef GRAPH_H
#define GRAPH_H

// 그래프 구조체 정의
typedef struct {
    int vertices;           // 정점의 수
    int** adjacencyMatrix; // 인접 행렬
    int isWeighted;        // 가중치 그래프 여부 (0: 무가중치, 1: 가중치)
} Graph;

// 그래프 생성 및 초기화
Graph* createGraph(int vertices);

// 간선 추가 함수
// src: 출발 정점, dest: 도착 정점, weight: 가중치
void addEdge(Graph* graph, int src, int dest, int weight);

// 그래프 메모리 해제
void destroyGraph(Graph* graph);

// 인접 정점 확인 함수
// 가중치가 있는 경우 가중치 반환, 없는 경우 1 반환, 연결되지 않은 경우 0 반환
int isAdjacent(Graph* graph, int src, int dest);

// 정점의 차수(degree) 계산
int getDegree(Graph* graph, int vertex);

// 그래프의 정점 수 반환
int getVertexCount(Graph* graph);

// 정점의 모든 인접 정점을 배열로 반환
// adjList: 인접 정점을 저장할 배열
// count: 인접 정점의 수를 저장할 포인터
void getAdjacentVertices(Graph* graph, int vertex, int* adjList, int* count);

// 그래프 유효성 검사
int isValidVertex(Graph* graph, int vertex);

// 방문 배열 생성 및 초기화
int* createVisitedArray(Graph* graph);

#endif // GRAPH_H