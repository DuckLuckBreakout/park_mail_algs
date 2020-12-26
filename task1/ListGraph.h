#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    explicit ListGraph(int vertexCount);
    explicit ListGraph(const IGraph &graph);
    ~ListGraph() override = default;
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyLists;
};

#endif //LISTGRAPH_H
