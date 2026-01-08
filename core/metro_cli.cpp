#include "metro_graph.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << R"({"error":"Usage: metro_cli <src_id> <dest_id>"})";
        return 1;
    }

    int src = std::stoi(argv[1]);
    int dest = std::stoi(argv[2]);

    MetroGraph metro;
    std::cout << metro.getRouteJSON(src, dest);
    return 0;
}
