#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int vertexCount);
    explicit MatrixGraph(const IGraph &graph);
    ~MatrixGraph() override = default;
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacencyMatrix;
};

#endif //MATRIXGRAPH_H
