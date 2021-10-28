#pragma once
#include <vector>
#include <queue>
#include <iostream>

template <typename DataType, typename Cost = int>
class AdjacencyMartixGraph
{
public:
    template <typename Visitor>
    void breadthFirstSearch(const Visitor& visit)
    {
        if (vertexs.empty())
            return;

        const size_t startVertexIndex = 0;

        std::vector<int8_t> visited(vertexs.size(), 0);
        std::queue<size_t> toVisit;

        visit(vertexs[startVertexIndex]);
        visited[startVertexIndex] = 1;
        toVisit.push(startVertexIndex);

        while (!toVisit.empty())
        {
            const auto currentIndex = toVisit.front();
            toVisit.pop();

            const auto& adjacencyList = adjacencyMartix[currentIndex];
            for (auto isAdjacent = adjacencyList.begin(); isAdjacent != adjacencyList.end(); isAdjacent++)
            {
                const size_t adjacencyVertexIndex = isAdjacent - adjacencyList.begin();

                if (*isAdjacent && !visited[adjacencyVertexIndex])
                {
                    visit(vertexs[adjacencyVertexIndex]);
                    visited[adjacencyVertexIndex] = 1;
                    toVisit.push(adjacencyVertexIndex);
                }
            }
        }
    }

    template <typename Visitor>
    void depthFirstSearch(const Visitor& visit)
    {
        if (vertexs.empty())
        {
            return;
        }

        std::vector<int8_t> visited(vertexs.size(), 0);
        const size_t startVertexIndex = 0;
        depthFirstSearchHelper(startVertexIndex, visit, visited);
    }

    void primMinimumSpanningTree() {
        std::vector<size_t> parent;
        parent.reserve(vertexNum);
        for (size_t i = 0; i < vertexNum; i++)
        {
            parent.push_back(i);
        }

        std::vector<Cost> cost(vertexNum, 0);
        std::vector<int8_t> visited(vertexNum, 0);

        size_t currentIndex = 0;
        visited[currentIndex] = 1;

        for (size_t j = 0; j < vertexNum; j++)
        {
            // find out closest vertex
            for (size_t adjaceny = 0; adjaceny < vertexNum; adjaceny++)
            {
                const auto adjacencyCost = adjacencyMartix[currentIndex][adjaceny];
                if (!visited[adjaceny] && adjacencyCost && (!cost[adjaceny] || adjacencyCost < cost[adjaceny]))
                {
                    cost[adjaceny] = adjacencyCost;
                    parent[adjaceny] = currentIndex;
                }
            }

            // caculate min cost and move to next vertex
            Cost minCost = 0;
            for (size_t i = 0; i < vertexNum; ++i)
            {
                if (cost[i] && (!minCost || cost[i] < minCost))
                {
                    minCost = cost[i];
                    currentIndex = i;
                }
            }
            visited[currentIndex] = 1;
            cost[currentIndex] = 0;
        }

        for (size_t i = 0; i < parent.size(); i++)
        {
            std::cout << parent[i] << "--" << i << ' ' << adjacencyMartix[parent[i]][i] << '\n';
        }
    }

    template <typename VertexGenerator, typename ArcGenerator>
    void createGraph(VertexGenerator&& generateVertex, ArcGenerator&& generateArc, bool directed = true)
    {
        std::cout << "vertex:\n";
        for (;;)
        {
            std::cout << vertexNum << ": ";
            const auto vertexData = generateVertex();

            if (!vertexData)
                break;

            vertexNum++;
            vertexs.push_back(*vertexData);
        }

        adjacencyMartix.resize(vertexNum, std::vector<Cost>(vertexNum, 0));

        std::cout << "arc:\n";
        for (;;)
        {
            std::cout << arcNum << ": ";
            const auto arcData = generateArc();

            if (!arcData)
                break;

            arcNum++;
            auto [source, target, cost] = *arcData;
            adjacencyMartix[source][target] = cost;
            if (!directed)
            {
                adjacencyMartix[target][source] = cost;
            }
        }

        std::cout << "adjacency martix:\n";
        for (const auto& line : adjacencyMartix)
        {
            for (const auto isAdjacency : line)
            {
                std::cout << static_cast<int>(isAdjacency) << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "vertex number: " << vertexNum << std::endl;
        std::cout << "arc number: " << arcNum << std::endl;
    }
private:
    std::vector<DataType> vertexs;
    std::vector<std::vector<Cost>> adjacencyMartix;
    size_t vertexNum = 0;
    size_t arcNum = 0;

    template <typename Visitor>
    void depthFirstSearchHelper(const size_t parentVertexIndex, const Visitor& visit, std::vector<int8_t>& visited)
    {
        if (visited[parentVertexIndex])
        {
            return;
        }

        const auto& parentVertexData = vertexs[parentVertexIndex];
        visit(parentVertexData);
        visited[parentVertexIndex] = 1;

        const auto& adjacencyList = adjacencyMartix[parentVertexIndex];
        for (auto isAdjacent = adjacencyList.begin(); isAdjacent != adjacencyList.end(); isAdjacent++)
        {
            const size_t adjacencyVertexIndex = isAdjacent - adjacencyList.begin();

            if (*isAdjacent && !visited[adjacencyVertexIndex])
            {
                depthFirstSearchHelper(adjacencyVertexIndex, visit, visited);
            }
        }
    }
};
