#include "AStarAlgorithm.h"

/**
 * \brief Contructor sets up the multidimensional matrix basePathMatrix
 */
AStarAlgorithm::AStarAlgorithm()
{
    for (int i = 0; i < MAPROWS; i++)
    {
        basePathMatrix[i] = new int[MAPCOLUMNS];
    }
}

/**
 * \brief Returns the matrix with the shortest path it found to get from the start to the finish indicated by elementsMatrix.
 * This function DOES NOT do the actual finding of the path, it only sets up the initial conditions and makes the recursive call to
 * the function recursivePathing.
 * @param elementsMatrix Matrix received from the client with the obstacles (1) the start (3) and the finish (2) of the game board
 * @return basePathMatrix Matrix with the first found path from the start to the finish indicated by the 3 and 2 respectively in elementsMatrix
 */
int **AStarAlgorithm::findPath(int elementsMatrix[MAPROWS][MAPCOLUMNS])
{
    int initialPoint[2];
    // look for first element position and final element position and add them to closedList
    for (int i = 0; i < MAPROWS; i++)
    {
        for (int j = 0; j < MAPCOLUMNS; j++)
        {
            receivedElementsMatrix[i][j] = elementsMatrix[i][j];
            basePathMatrix[i][j] = 0;
            if (elementsMatrix[i][j] == 3)
            {
                initialPoint[0] = i;
                initialPoint[1] = j;
            }
            if (elementsMatrix[i][j] == 2)
            {
                this->finalPoint[0] = i;
                this->finalPoint[1] = j;
            }
        }
    }
    this->closedList.push_back(coordsToIndex(initialPoint));
    // setup heuristic map
    // execute pathfind
}

int AStarAlgorithm::coordsToIndex(int coords[2])
{
    int row = coords[0];
    int column = coords[1];
    return row * MAPCOLUMNS + column;
}

int *AStarAlgorithm::indexToCoords(int index)
{
    int row = (int)index / MAPCOLUMNS;
    int column = index % MAPCOLUMNS;
    int coords[2] = {row, column};
    return coords;
}