#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertexCount) : vertexCount(vertexCount), adjacencyArray() {}


ArcGraph::ArcGraph(const IGraph &graph) : vertexCount(graph.VerticesCount()), adjacencyArray() {
    for (int i = 0; i < vertexCount; i++)
        for (auto &vertex : graph.GetNextVertices(i))
            adjacencyArray.emplace_back(i, vertex);
}


void ArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 and from < vertexCount);
    assert(to >= 0 and to < vertexCount);
    adjacencyArray.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return adjacencyArray.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 and vertex < vertexCount);
    std::vector<int> result;
    for (auto &adjacencyPair : adjacencyArray)
        if (adjacencyPair.first == vertex)
            result.push_back(adjacencyPair.second);
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 and vertex < vertexCount);
    std::vector<int> result;
    for (auto &adjacencyPair : adjacencyArray)
        if (adjacencyPair.second == vertex)
            result.push_back(adjacencyPair.first);
    return result;
}
