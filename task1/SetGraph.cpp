#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) : adjacencyVertices(vertexCount) {}

SetGraph::SetGraph(const IGraph &graph) : adjacencyVertices(graph.VerticesCount()) {
    for (int i = 0; i < adjacencyVertices.size(); i++)
        for (auto &vertex : graph.GetNextVertices(i))
            adjacencyVertices[i].insert(vertex);
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 and from < adjacencyVertices.size());
    assert(to >= 0 and to < adjacencyVertices.size());
    adjacencyVertices[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjacencyVertices.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 and vertex < adjacencyVertices.size());
    std::vector<int> result;
    for (const int &adjacencyVertex : adjacencyVertices[vertex])
        result.push_back(adjacencyVertex);
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 and vertex < adjacencyVertices.size());
    std::vector<int> result;
    for (int i = 0; i < adjacencyVertices.size(); i++)
        if (adjacencyVertices[i].find(vertex) != adjacencyVertices[i].end())
            result.push_back(i);
    return result;
}

