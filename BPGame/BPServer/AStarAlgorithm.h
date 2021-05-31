#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include "../../LinkedList/List.h"
#include "MapConstants.h"

//! Class in charge of carrying out the A* Pathfinding algorithm
class AStarAlgorithm
{
private:
    //! struct used to represent the nodes on the map for the pathfinding algorithm
    struct ANode
    {
        bool obstacle = false;
        bool visited = false;
        int HValue = 0;
        int FValue = 1000000;
        int totalDistance = 0;
        int index;
        int x; // column
        int y; // row
        List<ANode *> neighbors;
        ANode *parent = nullptr;
    };

    //! Position of the final point of the received matrix from the client
    ANode *finalNode;

    //! Node where algorightm starts
    ANode *startNode;

    //! The list of nodes that have already been visited
    List<int> closedList;

    //! The list of nodes that are currently considered to be visited
    List<int> openList;

    //! The matrix of nodes
    ANode *nodes = nullptr;

    //! Matrix received from the client, contains the obstacles, start and finish.
    int receivedElementsMatrix[MAPROWS][MAPCOLUMNS]{}; // 7 rows, 11 columns

    //!Empty Base matrix which will be filled with the shortest path when the function find path is called
    int **basePathMatrix = new int *[MAPROWS];

    int coordsToIndex(int coords[2]); // coords are always [rows, colums]

    List<int> indexToCoords(int index);

    void addNeighborsToOpenList(ANode *node);

    void AStarPathfind();

    int distance(ANode node1, ANode node2);

    int findMinOpenNode();

public:
    AStarAlgorithm();
    int **findPath(int elementsMatrix[MAPROWS][MAPCOLUMNS]);
};

#endif //ASTAR_ALGORITHM_H
