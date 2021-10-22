#pragma once
#include <vector>
#include <queue>
#include <iostream>

template <typename DataType>
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

    template <typename VertexGenerator, typename ArcGenerator>
    void createGraph(VertexGenerator&& generateVertex, ArcGenerator&& generateArc)
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

        adjacencyMartix.resize(vertexNum, std::vector<int8_t>(vertexNum, 0));

        std::cout << "arc:\n";
        for (;;)
        {
            std::cout << arcNum << ": ";
            const auto arcData = generateArc();

            if (!arcData)
                break;

            arcNum++;
            auto [source, target] = *arcData;
            adjacencyMartix[source][target] = 1;
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
    std::vector<std::vector<int8_t>> adjacencyMartix;
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
