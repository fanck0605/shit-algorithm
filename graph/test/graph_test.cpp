#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include "adjacency_list_graph.h"
#include "adjacency_martix_graph.h"

int main()
{
    AdjacencyListGraph<std::string> adjacencyListGraph;

    std::vector<std::string> vertexData{ "d", "a", "b", "c", "e" };
    std::vector<std::pair<size_t, size_t>> arcData{
        {0, 1},
        {0, 3},
        {1, 2},
        {1, 3},
        {3, 4}
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
        std::cout << current->first << ' ' << current->second << std::endl;
        return *current++;
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
    }, [current = arcData.begin(), end = arcData.end()]() mutable->std::optional<std::pair<size_t, size_t>>
    {
        if (current == end)
        {
            std::cout << "end" << std::endl;
            return std::nullopt;
        }
        std::cout << current->first << ' ' << current->second << std::endl;
        return *current++;
    });

    std::cout << "breadth first search: \n";
    adjacencyMartixGraph.breadthFirstSearch([](const std::string& data)
        { std::cout << data << ' '; });
    std::cout << std::endl;

    std::cout << "depth first search: \n";
    adjacencyMartixGraph.depthFirstSearch([](const std::string& data)
        { std::cout << data << ' '; });
    std::cout << std::endl;

    return 0;
}
