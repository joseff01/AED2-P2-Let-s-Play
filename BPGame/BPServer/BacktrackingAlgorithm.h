#ifndef BPSERVER_BACKTRACKINGALGORITHM_H
#define BPSERVER_BACKTRACKINGALGORITHM_H


class BacktrackingAlgorithm {
private:
    /**
     * Counter for the step by step path for the findPathfunction
     */
    int counterPath = 1;
    /**
     * Position of the final point of the received matrix from the client
     */
    int finalPoint[2] = {0,0};
    /**
     * Matrix received from the client, contains the obstacles, start and finish.
     */
    int receivedElementsMatrix[7][9]{};
    /**
     * Empty Base matrix which will be filled with the first found path when the function find path is called
     */
    int** basePathMatrix = new int*[7];
    void basePathMatrixAssignation();
    bool recursivePathing(const int initialPoint[2]);
public:
    BacktrackingAlgorithm();
    int** findPath(int elementsMatrix[7][9]);
};


#endif //BPSERVER_BACKTRACKINGALGORITHM_H
