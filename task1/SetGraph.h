#ifndef SETGRAPH_H
#define SETGRAPH_H

#include <unordered_set>
#include "IGraph.h"


class SetGraph : public IGraph {
public:
    explicit SetGraph(int vertexCount);
    explicit SetGraph(const IGraph &graph);
    ~SetGraph() override = default;
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> adjacencyVertices;
};

#endif //SETGRAPH_H
