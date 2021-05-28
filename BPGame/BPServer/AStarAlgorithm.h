#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include "List.h"
#include "MapConstants.h"

class AStarAlgorithm
{
private:
    //! Position of the final point of the received matrix from the client
    int finalPoint[2];

    List<int> closedList;

    List<int> openList;

    //! Matrix received from the client, contains the obstacles, start and finish.
    int receivedElementsMatrix[MAPROWS][MAPCOLUMNS]{}; // 7 rows, 11 columns

    //! Heuristic map calculated at start of algorithm
    int heuristicMap[MAPROWS][MAPCOLUMNS];

    //!Empty Base matrix which will be filled with the shortest path when the function find path is called
    int **basePathMatrix = new int *[MAPROWS];

    int coordsToIndex(int coords[2]); // coords are always [rows, colums]

    int *indexToCoords(int index);

public:
    AStarAlgorithm();
    int **findPath(int elementsMatrix[MAPROWS][MAPCOLUMNS]);
};

#endif //ASTAR_ALGORITHM_H
