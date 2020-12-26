#include "ListGraph.h"

ListGraph::ListGraph(int vertexCount) : adjacencyLists(vertexCount) {}

ListGraph::ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {
    for (int i = 0; i < adjacencyLists.size(); i++)
        for (auto &vertex : graph.GetNextVertices(i))
            adjacencyLists[i].push_back(vertex);
}

void ListGraph::AddEdge(int from, int to) {
    assert(from >= 0 and from < adjacencyLists.size());
    assert(to >= 0 and to < adjacencyLists.size());
    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 and vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 and vertex < adjacencyLists.size());
    std::vector<int> result;
    for (int from = 0; from < adjacencyLists.size(); from++)
        for (int i = 0; i < adjacencyLists[from].size(); i++)
            if (adjacencyLists[from][i] == vertex)
                result.push_back(from);
    return result;
}
