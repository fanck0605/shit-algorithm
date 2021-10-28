#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <tuple>
#include "adjacency_list_graph.h"
#include "adjacency_martix_graph.h"

int main()
{
    AdjacencyListGraph<std::string> adjacencyListGraph;

    std::vector<std::string> vertexData{ "d", "a", "b", "c", "e" };
    std::vector<std::tuple<size_t, size_t, int>> arcData{
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    adjacencyListGraph.createGraph([current = vertexData.begin(), end = vertexData.end()]() mutable->std::optional<std::string>
    {
        if (current == end)
        {
            std::cout << "end" << std::endl;
            return std::nullopt;
        }
        std::cout << *current << std::endl;
        return *current++;
    }, [current = arcData.begin(), end = arcData.end()]() mutable->std::optional<std::pair<size_t, size_t>>
    {
        if (current == end)
        {
            std::cout << "end" << std::endl;
            return std::nullopt;
        }

        auto [source, target, cost] = *current++;
        std::cout << source << "--" << target << ' ' << cost << std::endl;
        return std::make_pair(source, target);
    });

    std::cout << "breadth first search: \n";
    adjacencyListGraph.breadthFirstSearch([](const std::string& data)
        { std::cout << data << ' '; });
    std::cout << std::endl;

    std::cout << "depth first search: \n";
    adjacencyListGraph.depthFirstSerach([](const std::string& data)
        { std::cout << data << ' '; });
    std::cout << std::endl;

    AdjacencyMartixGraph<std::string> adjacencyMartixGraph;

    adjacencyMartixGraph.createGraph([current = vertexData.begin(), end = vertexData.end()]() mutable->std::optional<std::string>
    {
        if (current == end)
        {
            std::cout << "end" << std::endl;
            return std::nullopt;
        }
        std::cout << *current << std::endl;
        return *current++;
    }, [current = arcData.begin(), end = arcData.end()]() mutable->std::optional<std::tuple<size_t, size_t, int>>
    {
        if (current == end)
        {
            std::cout << "end" << std::endl;
            return std::nullopt;
        }

        auto [source, target, cost] = *current;
        std::cout << source << "--" << target << ' ' << cost << std::endl;
        return *current++;
    }, false);

    std::cout << "breadth first search: \n";
    adjacencyMartixGraph.breadthFirstSearch([](const std::string& data)
        { std::cout << data << ' '; });
    std::cout << std::endl;

    std::cout << "depth first search: \n";
    adjacencyMartixGraph.depthFirstSearch([](const std::string& data)
        { std::cout << data << ' '; });
    std::cout << std::endl;

    std::cout << "prim minimum spanning tree:\n";
    adjacencyMartixGraph.primMinimumSpanningTree();

    return 0;
}
