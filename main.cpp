#include <iostream>
#include "src/Node.h"
#include <thread>

auto main(int argc, char** argv) -> int
{
    if (argc < 5)
    {
        std::cerr << "./gossip <id> <your port>  <neighbor1 port>   <neighbor2 port>" << std::endl;
        return -1;
    }

    Node n1(std::stoi(argv[1]), std::stoi(argv[2]));
    n1.startGossip();

    std::vector<int> other_neighbors{std::stoi(argv[3]), std::stoi(argv[4])};
    const std::string message = "hello from " + std::to_string(n1.getId());

    for (const auto neighbor : other_neighbors)
    {
        n1.addNeighbor(neighbor);
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    n1.sendGossip(message);

    return 0;
}
