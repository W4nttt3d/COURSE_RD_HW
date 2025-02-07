#pragma once
#include <vector>
#include <unordered_map>
#include <list>
#include <functional>
#include <set>

class Graph {
public:
    Graph(unsigned numVertices);

    void addEdge(unsigned x, unsigned y);
    std::vector<unsigned> bfs(unsigned start, unsigned destination);
    std::vector<unsigned> aStar(unsigned start, unsigned destination, const std::function<float(unsigned, unsigned)>& heuristic);


private:
    unsigned numVertices;
    std::unordered_map<unsigned, std::list<unsigned>> m_adjacencyList;
};
