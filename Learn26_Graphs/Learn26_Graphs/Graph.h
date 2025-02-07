#pragma once
#include <vector>
#include <unordered_map>
#include <list>

class Graph {
public:
    Graph(unsigned numVertices);

    void addEdge(unsigned x, unsigned y);

    std::vector<unsigned> bfs(unsigned start, unsigned destination);

private:
    unsigned numVertices;
    std::unordered_map<unsigned, std::list<unsigned>> m_adjacencyList;
};
