#ifndef BPSERVER_BACKTRACKINGALGORITHM_H
#define BPSERVER_BACKTRACKINGALGORITHM_H


class BacktrackingAlgorithm {
private:
    int counterPath = 1;
    int finalPoint[2] = {0,0};
    int receivedElementsMatrix[7][9]{};
    int** basePathMatrix = new int*[7];
    void basePathMatrixAssignation();
    bool recursivePathing(const int initialPoint[2]);
public:
    BacktrackingAlgorithm();
    int** findPath(int elementsMatrix[7][9]);
};


#endif //BPSERVER_BACKTRACKINGALGORITHM_H
