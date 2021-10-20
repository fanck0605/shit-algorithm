#pragma once
#include <vector>
#include <queue>
#include <iostream>

template <typename DataType>
class AdjacencyListGraph
{
public:
    struct ArcNode
    {
        size_t adjacencyVertexIndex;
        ArcNode *nextArc;

        ArcNode(const size_t adjacencyVertexIndex, ArcNode *const nextArc = nullptr)
            : adjacencyVertexIndex(adjacencyVertexIndex), nextArc(nextArc) {}

        friend std::ostream &operator<<(std::ostream &os, ArcNode const *const arc)
        {
            const ArcNode *current = arc;

            os << '[';
            if (current)
            {
                os << current->adjacencyVertexIndex;
                current = current->nextArc;
            }
            while (current)
            {
                os << ", " << current->adjacencyVertexIndex;
                current = current->nextArc;
            }
            os << ']';

            return os;
        }
    };

    struct VertexNode
    {
        DataType data{};
        ArcNode *firstArc = nullptr;

        friend std::ostream &operator<<(std::ostream &os, const VertexNode &node)
        {
            os << node.data << ": " << node.firstArc;
            return os;
        }
    };

    // BFS
    template <typename Visitor>
    void breadthFirstSearch(const Visitor &visit)
    {
        if (adjacencyList.empty())
            return;

        std::vector<bool> visited(adjacencyList.size(), false);
        std::queue<size_t> toVisit;

        const size_t startVertexIndex = 0;

        toVisit.push(startVertexIndex);

        while (!toVisit.empty())
        {
            const auto currentIndex = toVisit.front();
            toVisit.pop();

            const VertexNode &current = adjacencyList[currentIndex];

            visit(current.data);
            visited[currentIndex] = true;

            const ArcNode *arc = current.firstArc;
            while (arc)
            {
                const size_t adjacencyVertexIndex = arc->adjacencyVertexIndex;

                if (!visited[adjacencyVertexIndex])
                {
                    toVisit.push(adjacencyVertexIndex);
                }

                arc = arc->nextArc;
            }
        }
    }

    // DFS
    template <typename Visitor>
    void depthFirstSerach(Visitor &&visit)
    {
    }

    template <typename VertexGenerator, typename ArcGenerator>
    void createGraph(VertexGenerator &&generateVertex, ArcGenerator &&generateArc)
    {
        std::cout << "vertex:\n";
        for (;;)
        {
            std::cout << vertexNum << ": ";
            const auto vertexData = generateVertex();

            if (!vertexData)
                break;

            vertexNum++;
            adjacencyList.push_back(VertexNode{*vertexData});
        }

        std::cout << "arc:\n";
        for (;;)
        {
            std::cout << arcNum << ": ";
            const auto arcData = generateArc();

            if (!arcData)
                break;

            arcNum++;
            auto [source, target] = *arcData;
            auto sourceVertex = adjacencyList.begin() + source;
            sourceVertex->firstArc = new ArcNode{target, sourceVertex->firstArc};
        }

        std::cout << "adjacency list:\n";
        for (const auto &vertex : adjacencyList)
        {
            std::cout << vertex << std::endl;
        }
        std::cout << "vertex number: " << vertexNum << std::endl;
        std::cout << "arc number: " << arcNum << std::endl;
    }

private:
    std::vector<VertexNode> adjacencyList;
    size_t vertexNum = 0;
    size_t arcNum = 0;
};
