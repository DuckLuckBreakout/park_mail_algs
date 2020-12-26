#include <queue>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

std::vector<int> checkGraphs(4, 0);

void BFS (const IGraph& graph, int vertex, void (*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);
        std::vector<int> adjacentVertices = graph.GetNextVertices(current);
        for (int &adjacentVertex : adjacentVertices)
            if(!visited[adjacentVertex]) {
                bfsQueue.push(adjacentVertex);
                visited[adjacentVertex] = true;
            }
    }
}

int main()
{
//  0---->1
//  | \  /
//  3   4--->2

    std::cout << std::endl << "ListGraph" << std::endl;
    ListGraph graph1(5);
    graph1.AddEdge( 0, 1 );
    graph1.AddEdge( 0, 3 );
    graph1.AddEdge( 0, 4 );
    graph1.AddEdge( 1, 4 );
    graph1.AddEdge( 4, 2 );

    BFS(graph1, 0, [](int vertex) {std::cout << vertex << ", "; checkGraphs[0]++;});

    std::cout << std::endl << "MatrixGraph" << std::endl;
    MatrixGraph graph2(5);
    graph2.AddEdge( 0, 1 );
    graph2.AddEdge( 0, 3 );
    graph2.AddEdge( 0, 4 );
    graph2.AddEdge( 1, 4 );
    graph2.AddEdge( 4, 2 );

    BFS(graph2, 0, [](int vertex) {std::cout << vertex << ", "; checkGraphs[1]++;});

    std::cout << std::endl << "ArcGraph" << std::endl;
    ArcGraph graph3(5);
    graph3.AddEdge( 0, 1 );
    graph3.AddEdge( 0, 3 );
    graph3.AddEdge( 0, 4 );
    graph3.AddEdge( 1, 4 );
    graph3.AddEdge( 4, 2 );

    BFS(graph3, 0, [](int vertex) {std::cout << vertex << ", "; checkGraphs[2]++;});

    std::cout << std::endl << "SetGraph" << std::endl;
    SetGraph graph4(5);
    graph4.AddEdge( 0, 1 );
    graph4.AddEdge( 0, 3 );
    graph4.AddEdge( 0, 4 );
    graph4.AddEdge( 1, 4 );
    graph4.AddEdge( 4, 2 );

    BFS(graph4, 0, [](int vertex) {std::cout << vertex << ", "; checkGraphs[3]++;});

    for (const int &result : checkGraphs)
        assert(result == 5);
    return 0;
}