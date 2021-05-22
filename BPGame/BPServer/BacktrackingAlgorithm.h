#ifndef BPSERVER_BACKTRACKINGALGORITHM_H
#define BPSERVER_BACKTRACKINGALGORITHM_H


class BacktrackingAlgorithm {
private:
    int counterPath = 1;
    int receivedElementsMatrix[7][9]{};
    int (*basePathMatrix)[9] = new int[7][9];
    bool recursivePathing(const int initialPoint[2]);
public:
    BacktrackingAlgorithm();
    void* findPath(int elementsMatrix[7][9]);
};


#endif //BPSERVER_BACKTRACKINGALGORITHM_H
