#include "AStarAlgorithm.h"
#include "math.h"
#include <stdexcept>

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
 * This function DOES NOT do the actual finding of the path, it sets up the initial conditions and transforms the matrix of nodes 
 * into a matrix of ints detailing the shortest path from start to finish.
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
                nodes[index].neighbors.push_back(&nodes[(i - 1) * MAPCOLUMNS + (j)]);
            if (i < MAPROWS - 1)
                nodes[index].neighbors.push_back(&nodes[(i + 1) * MAPCOLUMNS + (j)]);
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
    int c = 0;
    ANode *p = finalNode;
    while (p != nullptr)
    {
        p = p->parent;
        c++;
    }

    p = finalNode;
    while (p != nullptr)
    {
        basePathMatrix[p->y][p->x] = c;
        p = p->parent;
        c--;
    }

    return this->basePathMatrix;
}

/*!
 * \brief Transform an array representing 2D coordinates to their index for the map used by the algorithm
 * 
 * \param coords an int array consisting or {row, column} 
 * \return int the index of the node at the given coordinates
 */
int AStarAlgorithm::coordsToIndex(int coords[2])
{
    int row = coords[0];
    int column = coords[1];
    return row * MAPCOLUMNS + column;
}

/*!
 * \brief Transforms a given index for a node in the map used by this algorithm to the respective coordinates
 * 
 * \param index the index of the node for which coordinates you want to find
 * \return List<int> a list with format {row, column}
 */
List<int> AStarAlgorithm::indexToCoords(int index)
{
    int row = (int)index / MAPCOLUMNS;
    int column = index % MAPCOLUMNS;
    List<int> coords = {row, column};
    return coords;
}

/*!
 * \brief Method in charge of adding the (indexes of) unvisited nodes that neighbor a given node to the openList
 * 
 * \param currentNode the node for which you want to add the neighbors to openList
 */
void AStarAlgorithm::addNeighborsToOpenList(ANode *currentNode)
{
    for (int i = 0; i < currentNode->neighbors.length(); i++)
    {
        ANode *neighbor = currentNode->neighbors[i];
        if (neighbor->obstacle == false)
        {
            if (neighbor->visited == false)
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
}

/*!
 * \brief Calculates the distance between 2 given ondes using pythagoras theorem (and then flooring it to get an int)
 * 
 * \param node1
 * \param node2 
 * \return int of the given distance between the given nodes
 */
int AStarAlgorithm::distance(ANode node1, ANode node2)
{
    return (int)(sqrt(pow(node1.x - node2.x, 2) + pow(node1.y - node2.y, 2)) * 10);
}

/*!
 * \brief Finds the (index of) the node in the openList that currently has the lowest F value
 * 
 * \return int the index of the node with the lowest value in the openList
 */
int AStarAlgorithm::findMinOpenNode()
{
    int minIndex = -1;
    if (openList.length() > 0)
    {
        minIndex = openList[0];
    }
    for (int i = 1; i < this->openList.length(); i++)
    {
        ANode *currentMin = &nodes[openList[i]];
        ANode *possibleMin = &nodes[minIndex];
        if (nodes[openList[i]].FValue < nodes[minIndex].FValue)
        {
            minIndex = openList[i];
        }
    }
    if (minIndex == -1)
    {
        printf("mik");
    }
    return minIndex;
}

//! Method in charge of carrying out the process of linking the final node to the parent node with the shortest path possible
void AStarAlgorithm::AStarPathfind()
{
    ANode *current = this->startNode;
    while (current != finalNode)
    {
        current->visited = true;
        addNeighborsToOpenList(current);

        int nextNodeIndex = findMinOpenNode();
        if (nextNodeIndex == -1)
        {
            //throw std::invalid_argument("No possible path from ball to goal");
            return;
        }

        int OpenListRemoveIndex = this->openList.find(nextNodeIndex);
        this->openList.erase(OpenListRemoveIndex);
        this->closedList.push_back(nextNodeIndex);

        current = &nodes[nextNodeIndex];
    }
}