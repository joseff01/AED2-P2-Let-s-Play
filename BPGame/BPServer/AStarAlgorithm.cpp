#include "AStarAlgorithm.h"
#include "math.h"

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
    this->nodes = new ANode[MAPCOLUMNS * MAPROWS];

    int initialPoint[2];
    // look for first element position and final element position and add initial node to closedList
    for (int i = 0; i < MAPROWS; i++)
    {
        for (int j = 0; j < MAPCOLUMNS; j++)
        {
            this->receivedElementsMatrix[i][j] = elementsMatrix[i][j];
            this->basePathMatrix[i][j] = 0;

            int coords[2] = {i, j};
            int index = coordsToIndex(coords);

            this->nodes[index].x = j;
            this->nodes[index].y = i;

            this->nodes[index].index = index;

            if (elementsMatrix[i][j] == 3) // start node
            {
                this->nodes[index].FValue = 0;
                this->startNode = &this->nodes[index];
            }
            else if (elementsMatrix[i][j] == 2) // end node
            {
                this->finalNode = &this->nodes[index];
            }
            else if (elementsMatrix[i][j] == 1) // obstacle
            {
                this->nodes[index].obstacle = true;
            }
        }
    }

    // Second setup wave
    for (int i = 0; i < MAPROWS; i++)
    {
        for (int j = 0; j < MAPCOLUMNS; j++)
        {
            int coords[2] = {i, j};
            int index = coordsToIndex(coords);

            // Vertica/Horizontal neighbors
            if (i > 0)
                nodes[index].neighbors.push_back(&nodes[(i - 1) * MAPROWS + (j)]);
            if (i < MAPROWS - 1)
                nodes[index].neighbors.push_back(&nodes[(i + 1) * MAPROWS + (j)]);
            if (j > 0)
                nodes[index].neighbors.push_back(&nodes[(i)*MAPCOLUMNS + (j - 1)]);
            if (j < MAPCOLUMNS - 1)
                nodes[index].neighbors.push_back(&nodes[(i)*MAPCOLUMNS + (j + 1)]);

            // Diagonal neighbors
            if (i > 0 && j > 0)
                nodes[index].neighbors.push_back(&nodes[(i - 1) * MAPCOLUMNS + (j - 1)]);
            if (i < MAPROWS - 1 && j > 0)
                nodes[index].neighbors.push_back(&nodes[(i + 1) * MAPCOLUMNS + (j - 1)]);
            if (i > 0 && j < MAPCOLUMNS - 1)
                nodes[index].neighbors.push_back(&nodes[(i - 1) * MAPCOLUMNS + (j + 1)]);
            if (i < MAPROWS - 1 && j < MAPCOLUMNS - 1)
                nodes[index].neighbors.push_back(&nodes[(i + 1) * MAPCOLUMNS + (j + 1)]);

            // Heuristic calc
            int finalcoords[2] = {(*this->finalNode).y, (*this->finalNode).x};

            int heuristic = (int)(abs(coords[0] - finalcoords[0]) + abs(coords[1] - finalcoords[1])); //manhattan distance for heuristic
            nodes[index].HValue = heuristic;
        }
    }

    // execute pathfind
    AStarPathfind();

    // transform parent chain to incremental numbers in elementsMatrix
    int c = 1;
    ANode *p = finalNode;
    while (p->parent != nullptr)
    {
        p = p->parent;
        c++;
    }

    p = finalNode;
    while (p->parent != nullptr)
    {
        basePathMatrix[p->y][p->x] = c;
        p = p->parent;
        c--;
    }

    return this->basePathMatrix;
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

void AStarAlgorithm::addNeighborsToOpenList(ANode *currentNode)
{
    for (int i = 0; i < currentNode->neighbors.length(); i++)
    {
        ANode *neighbor = currentNode->neighbors[i];
        if (neighbor->visited == false && neighbor->obstacle == false)
        {
            if (openList.find(neighbor->index) == -1) // this means neighbor's index is NOT in openList yet
            {
                openList.push_back(neighbor->index);
            }
        }

        int possibleFValue = currentNode->FValue + distance(*currentNode, *neighbor);

        if (possibleFValue < neighbor->FValue)
        {
            neighbor->parent = currentNode;
            neighbor->totalDistance = currentNode->totalDistance + distance(*currentNode, *neighbor);
            neighbor->FValue = neighbor->totalDistance + neighbor->HValue;
        }
    }
}

int AStarAlgorithm::distance(ANode node1, ANode node2)
{
    return (int)(sqrt(pow(node1.x - node2.x, 2) + pow(node1.y - node2.y, 2)) * 10);
}

int AStarAlgorithm::findMinOpenNode()
{
    int minIndex = 0;
    for (int i = 0; i < this->openList.length(); i++)
    {
        if (nodes[openList[i]].FValue < nodes[minIndex].FValue)
        {
            minIndex = openList[i];
        }
    }
    return minIndex;
}

void AStarAlgorithm::AStarPathfind()
{
    ANode *current = this->startNode;
    while (current != finalNode)
    {
        current->visited = true;
        addNeighborsToOpenList(current);

        int nextNodeIndex = findMinOpenNode();

        int OpenListRemoveIndex = this->openList.find(nextNodeIndex);
        this->openList.erase(OpenListRemoveIndex);
        this->closedList.push_back(nextNodeIndex);

        current = &nodes[nextNodeIndex];
    }
}