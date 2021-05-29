#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include "List.h"
#include "MapConstants.h"

class AStarAlgorithm
{
private:
    struct ANode
    {
        bool obstacle = false;
        bool visited = false;
        int HValue = 0;
        int FValue = 0;
        int x; // column
        int y; // row
        List<ANode> neighbors;
        ANode *parent = nullptr;
    };

    //! Position of the final point of the received matrix from the client
    ANode *finalNode;

    //! Node where algorightm starts
    ANode *startNode;

    List<int> closedList;

    List<int> openList;

    List<ANode> nodes;

    //! Matrix received from the client, contains the obstacles, start and finish.
    int receivedElementsMatrix[MAPROWS][MAPCOLUMNS]{}; // 7 rows, 11 columns

    //!Empty Base matrix which will be filled with the shortest path when the function find path is called
    int **basePathMatrix = new int *[MAPROWS];

    int coordsToIndex(int coords[2]); // coords are always [rows, colums]

    List<int> indexToCoords(int index);

public:
    AStarAlgorithm();
    int **findPath(int elementsMatrix[MAPROWS][MAPCOLUMNS]);
};

#endif //ASTAR_ALGORITHM_H
