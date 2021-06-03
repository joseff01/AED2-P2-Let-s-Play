#include <iostream>
#include "BPServer.h"
#include "BacktrackingAlgorithm.h"
#include "AStarAlgorithm.h"
#include "../../LinkedList/List.h"

bool checkForThree(int matrix[MAPROWS][MAPCOLUMNS])
{
    for (int i = 0; (i < 7); i++)
    {
        for (int j = 0; (j < 11); j++)
        {
            if (matrix[i][j] == 3)
            {
                return true;
            }
        }
    }
    return false;
}

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

    while (true)
    {
        bpServer.readBuffer();
        json jsonMsg = bpServer.getBuffer();
        switch ((int)jsonMsg["algorithm"])
        {
        case 0:
        { //A*
            bpServer.readBuffer();
            jsonMsg = bpServer.getBuffer();

            List<List<int>> badList = jsonMsg["matrix"];
            List<List<int>> list = bpServer.fixMatrix(badList);

            int matrix[7][11];
            for (unsigned i = 0; (i < 7); i++)
            {
                for (unsigned j = 0; (j < 11); j++)
                {
                    matrix[i][j] = list[i][j];
                }
            }
            int **resultMatrix;
            if (checkForThree)
            {
                AStarAlgorithm aStarAlgorithm = AStarAlgorithm();
                resultMatrix = aStarAlgorithm.findPath(matrix);
            }
            else
            {
                for (unsigned i = 0; (i < 7); i++)
                {
                    for (unsigned j = 0; (j < 11); j++)
                    {
                        resultMatrix[i][j] = 0;
                    }
                }
            }

            List<List<int>> resultList;
            for (unsigned i = 0; (i < 7); i++)
            {
                List<int> resultColumn;
                for (unsigned j = 0; (j < 11); j++)
                {
                    resultColumn.push_back(resultMatrix[i][j]);
                }
                resultList.push_back(resultColumn);
            }
            jsonMsg["matrix"] = resultList;
            bpServer.sendBuffer(jsonMsg);
            break;
        }

        case 1:
        { //Backtracking
            bpServer.readBuffer();
            jsonMsg = bpServer.getBuffer();

            List<List<int>> badList = jsonMsg["matrix"];
            List<List<int>> list = bpServer.fixMatrix(badList);

            int matrix[7][11];
            for (unsigned i = 0; (i < 7); i++)
            {
                for (unsigned j = 0; (j < 11); j++)
                {
                    matrix[i][j] = list[i][j];
                }
            }
            int **resultMatrix;
            if (checkForThree(matrix))
            {
                BacktrackingAlgorithm backtrackingAlgorithm = BacktrackingAlgorithm();
                resultMatrix = backtrackingAlgorithm.findPath(matrix);
            }
            else
            {
                for (unsigned i = 0; (i < 7); i++)
                {
                    for (unsigned j = 0; (j < 11); j++)
                    {
                        resultMatrix[i][j] = 0;
                    }
                }
            }
            List<List<int>> resultList;
            for (unsigned i = 0; (i < 7); i++)
            {
                List<int> resultColumn;
                for (unsigned j = 0; (j < 11); j++)
                {
                    resultColumn.push_back(resultMatrix[i][j]);
                }
                resultList.push_back(resultColumn);
            }
            jsonMsg["matrix"] = resultList;
            bpServer.sendBuffer(jsonMsg);
            break;
        }

        case 3:
        { //stop Server
            bpServer.endServer();
            return (0);
        }
        }
    }
}