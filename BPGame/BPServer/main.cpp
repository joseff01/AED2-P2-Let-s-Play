#include <iostream>
#include "BPServer.h"
#include "BacktrackingAlgorithm.h"
#include "AStarAlgorithm.h"

int main()
{
    AStarAlgorithm *AStarAlgo = new AStarAlgorithm();
    int a[7][11] = {{0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 1, 1}, {2, 0, 0, 0, 1, 0, 0, 1, 3, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}};
    int **i = AStarAlgo->findPath(a);

    std::cout << "Original:\n";
    for (int o = 0; o < 7; o++)
    {
        for (int j = 0; j < 11; j++)
        {
            std::cout << a[o][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Pathfind:\n";

    for (int o = 0; o < 7; o++)
    {
        for (int j = 0; j < 11; j++)
        {
            std::cout << i[o][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    // BPServer *geneticServer = new BPServer();
    return 0;
}
