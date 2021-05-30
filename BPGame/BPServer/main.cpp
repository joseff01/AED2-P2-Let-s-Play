#include <iostream>
#include "BPServer.h"
#include "BacktrackingAlgorithm.h"
#include "AStarAlgorithm.h"
#include "list.h"

int main()
{
    /*   std::cout << "Indexed:\n";
    for (int o = 0; o < 7; o++)
    {
        for (int j = 0; j < 11; j++)
        {
            std::cout << o * 11 + j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    int a[7][11] = {{0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 3}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 1, 1}, {2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}};

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

    AStarAlgorithm *AStarAlgo = new AStarAlgorithm();
    int **i = AStarAlgo->findPath(a);

    std::cout << "Pathfind:\n";

    for (int o = 0; o < 7; o++)
    {
        for (int j = 0; j < 11; j++)
        {
            std::cout << i[o][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
    BPServer bpServer = BPServer();

    while(true) {
        bpServer.readBuffer();
        json jsonMsg = bpServer.getBuffer();
        switch ((int)jsonMsg["algorithm"]) {
            case 0: { //A*
                bpServer.readBuffer();
                jsonMsg = bpServer.getBuffer();
                std::vector<std::vector<int>> vector = jsonMsg["matrix"];
                int matrix[7][11];
                for (unsigned i = 0; (i < 7); i++) {
                    for (unsigned j = 0; (j < 11); j++) {
                        matrix[i][j] = vector[i][j];
                    }
                }
                AStarAlgorithm aStarAlgorithm = AStarAlgorithm();
                int **resultMatrix = aStarAlgorithm.findPath(matrix);
                std::vector<std::vector<int>> resultVector;
                for (unsigned i = 0; (i < 7); i++) {
                    for (unsigned j = 0; (j < 11); j++) {
                        resultVector[i][j] = resultMatrix[i][j];
                    }
                }
                jsonMsg["matrix"] = resultVector;
                bpServer.sendBuffer(jsonMsg);
                break;
            }

            case 1: { //Backtracking
                bpServer.readBuffer();
                jsonMsg = bpServer.getBuffer();
                std::vector<std::vector<int>> vector = jsonMsg["matrix"];
                int matrix[7][11];
                for (unsigned i = 0; (i < 7); i++) {
                    for (unsigned j = 0; (j < 11); j++) {
                        matrix[i][j] = vector[i][j];
                    }
                }
                BacktrackingAlgorithm backtrackingAlgorithm = BacktrackingAlgorithm();
                int **resultMatrix = backtrackingAlgorithm.findPath(matrix);
                std::vector<std::vector<int>> resultVector;
                for (unsigned i = 0; (i < 7); i++) {
                    for (unsigned j = 0; (j < 11); j++) {
                        resultVector[i][j] = resultMatrix[i][j];
                    }
                }
                jsonMsg["matrix"] = resultVector;
                bpServer.sendBuffer(jsonMsg);
                break;
                }

            case 3: { //stop Server
                bpServer.endServer();
                return(0);
            }
        }
    }
}
