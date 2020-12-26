#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexCount) : adjacencyMatrix(vertexCount, std::vector<bool>(vertexCount)) {}

MatrixGraph::MatrixGraph(const IGraph &graph) : adjacencyMatrix(graph.VerticesCount(),
                                                                std::vector<bool>(graph.VerticesCount())) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        for (auto &vertex : graph.GetNextVertices(i))
            adjacencyMatrix[i][vertex] = true;
}


void MatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 and from < adjacencyMatrix.size());
    assert(to >= 0 and to < adjacencyMatrix.size());
    adjacencyMatrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 and vertex < adjacencyMatrix.size());
    std::vector<int> result;
    for (int to = 0; to < adjacencyMatrix.size(); to++)
        if (adjacencyMatrix[vertex][to])
            result.push_back(to);
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 and vertex < adjacencyMatrix.size());
    std::vector<int> result;
    for (int from = 0; from < adjacencyMatrix.size(); from++)
        if (adjacencyMatrix[from][vertex])
            result.push_back(from);
    return result;
}

