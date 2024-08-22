#include "Graph.h"
#include <queue>
#include <algorithm>

Graph::Graph(unsigned numVertices) : numVertices(numVertices) {}

void Graph::addEdge(unsigned x, unsigned y)
{
    m_adjacencyList[x].push_back(y);
    m_adjacencyList[y].push_back(x); 
}

std::vector<unsigned> Graph::bfs(unsigned start, unsigned destination)
{
    std::vector<unsigned> path;
    if (start == destination) {
        path.push_back(start);
        return path;
    }

    std::vector<unsigned> cameFrom(numVertices, static_cast<unsigned>(-1)); 
    std::vector<bool> visited(numVertices, false);
    std::queue<unsigned> frontier;
    frontier.push(start);
    visited[start] = true;

    while (!frontier.empty())
    {
        unsigned current = frontier.front();
        frontier.pop();

        if (current == destination)
        {
            for (unsigned step = destination; step != static_cast<unsigned>(-1); step = cameFrom[step])
            {
                path.push_back(step);
                if (step == start) break;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto it = m_adjacencyList.find(current);
        if (it != m_adjacencyList.end())
        {
            for (unsigned neighbor : it->second)
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    cameFrom[neighbor] = current;
                    frontier.push(neighbor);
                }
            }
        }
    }

    return path;
}
