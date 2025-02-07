#include "Graph.h"
#include <queue>
#include <unordered_map>
#include <vector>

Graph::Graph(unsigned numVertices) : numVertices(numVertices) {}

void Graph::addEdge(unsigned x, unsigned y) 
{
    m_adjacencyList[x].push_back(y);
    m_adjacencyList[y].push_back(x);
}

std::vector<unsigned> Graph::bfs(unsigned start, unsigned destination) 
{
    std::vector<unsigned> path;
    if (start == destination) 
    {
        path.push_back(start);
        return path;
    }

    std::unordered_map<unsigned, unsigned> parent;
    std::unordered_map<unsigned, bool> visited;
    std::queue<unsigned> queue;

    queue.push(start);
    visited[start] = true;
    parent[start] = start;

    while (!queue.empty()) 
    {
        unsigned node = queue.front();
        queue.pop();

        if (node == destination) 
        {
            unsigned current = destination;

            while (current != start) 
            {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (unsigned neighbor : m_adjacencyList[node])
        {
            if (!visited[neighbor]) 
            {
                queue.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = node;
            }
        }
    }

    return path; 
}
