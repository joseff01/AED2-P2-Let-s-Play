#include <iostream>
#include "BPServer.h"
#include "BacktrackingAlgorithm.h"

int main() {
    /*auto* backtrackingAlgorithm = new BacktrackingAlgorithm();
    int a[7][9] = {{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{2,0,0,0,1,0,0,0,3},{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0,0}};
    int** i = backtrackingAlgorithm->findPath(a);
    for (int o = 0; o < 7; o++){
        for (int j = 0; j < 9; j++){
            std::cout << i[o][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
     */
    BPServer* geneticServer = new BPServer();
    return 0;
}
