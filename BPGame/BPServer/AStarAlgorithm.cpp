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
            this->receivedElementsMatrix[i][j] = elementsMatrix[i][j];
            this->basePathMatrix[i][j] = 0;

            ANode current;
            current.x = j;
            current.y = i;

            int coords[2] = {i, j};

            int index = coordsToIndex(coords);

            if (elementsMatrix[i][j] == 3)
            {
                current.visited = true;
                this->closedList.push_back(index);
                this->nodes.push_back(current);
                this->startNode = &this->nodes[index];
            }
            else if (elementsMatrix[i][j] == 2)
            {
                this->nodes.push_back(current);
                this->finalNode = &this->nodes[index];
            }
            else if (elementsMatrix[i][j] == 1)
            {
                current.obstacle = true;
                this->nodes.push_back(current);
            }
            else
            {
                this->nodes.push_back(current);
            }
        }
    }
    for (int i = 0; i < MAPROWS; i++)
    {
        for (int j = 0; j < MAPCOLUMNS; j++)
        {
            int coords[2] = {i, j};
            int index = coordsToIndex(coords);
            if (i > 0)
                nodes[index].neighbors.push_back(nodes[(i - 1) * MAPROWS + (j)]);
            if (i < MAPROWS - 1)
                nodes[index].neighbors.push_back(nodes[(i + 1) * MAPROWS + (j)]);
            if (j > 0)
                nodes[index].neighbors.push_back(nodes[(i)*MAPCOLUMNS + (j - 1)]);
            if (j < MAPCOLUMNS - 1)
                nodes[index].neighbors.push_back(nodes[(i)*MAPCOLUMNS + (j + 1)]);

            // Diagonal connections
            if (i > 0 && j > 0)
                nodes[index].neighbors.push_back(nodes[(i - 1) * MAPCOLUMNS + (j - 1)]);
            if (i < MAPROWS - 1 && j > 0)
                nodes[index].neighbors.push_back(nodes[(i + 1) * MAPCOLUMNS + (j - 1)]);
            if (i > 0 && j < MAPCOLUMNS - 1)
                nodes[index].neighbors.push_back(nodes[(i - 1) * MAPCOLUMNS + (j + 1)]);
            if (i < MAPROWS - 1 && j < MAPCOLUMNS - 1)
                nodes[index].neighbors.push_back(nodes[(i + 1) * MAPCOLUMNS + (j + 1)]);
        }
    }

    //Setup neighbors

    // add starter neigbors to open list

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

List<int> AStarAlgorithm::indexToCoords(int index)
{
    int row = (int)index / MAPCOLUMNS;
    int column = index % MAPCOLUMNS;
    List<int> coords = {row, column};
    return coords;
}