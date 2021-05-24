#include "BacktrackingAlgorithm.h"
#include <iostream>

void BacktrackingAlgorithm::basePathMatrixAssignation(){
    for (int i = 0; i < 7; i++){
        basePathMatrix[i] = new int[9];
    }
}

int** BacktrackingAlgorithm::findPath(int elementsMatrix[7][9]){
    int initialPoint[2];
    finalPoint[0] = 0;
    finalPoint[1] = 0;
    counterPath = 1;
    //Search for first element position AND copy the received matrix to the attribute in BacktrackingAlgorithm
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 9; j++){
            receivedElementsMatrix[i][j] = elementsMatrix[i][j];
            basePathMatrix[i][j] = 0;
            if (elementsMatrix[i][j] == 3){
                initialPoint[0] = i;
                initialPoint[1] = j;
            } if (elementsMatrix[i][j] == 2){
                finalPoint[0] = i;
                finalPoint[1] = j;
            }
        }
    }
    recursivePathing(initialPoint);
    return basePathMatrix;
}

bool BacktrackingAlgorithm::recursivePathing(const int initialPoint[2]) {
    int row = initialPoint[0];
    int column = initialPoint[1];
    basePathMatrix[row][column] = counterPath;

    //west movement
    if (((row < 7)&&(0 <= row)) && ((column - 1 < 9)&&(0 <= column - 1))) {
        if ((receivedElementsMatrix[row][column - 1] != 1) && (basePathMatrix[row][column - 1] == 0)) {
            std::cout << "west" << std::endl;
            if (receivedElementsMatrix[row][column - 1] == 2) {
                std::cout << "W SUCCESS" << std::endl;
                basePathMatrix[row][column - 1] = counterPath + 1;
                return true;
            } else {
                counterPath++;
                int newInitialPoint[2] = {row, column - 1};
                if (recursivePathing(newInitialPoint)) {
                    return true;
                }
            }
        }
    }if ((finalPoint[0] - initialPoint[0]) > 0){
        //southwest movement
        if (((row + 1 < 7)&&(0 <= row + 1)) && ((column - 1 < 9)&&(0 <= column - 1))) {
            if ((receivedElementsMatrix[row + 1][column - 1] != 1) && (basePathMatrix[row + 1][column - 1] == 0)) {
                std::cout << "southwest" << std::endl;
                if (receivedElementsMatrix[row + 1][column - 1] == 2) {
                    std::cout << "SW SUCCESS" << std::endl;
                    basePathMatrix[row + 1][column - 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row + 1, column - 1};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
        //south movement
        if (((row + 1 < 7)&&(0 <= row + 1)) && ((column < 9)&&(0 <= column))) {
            if ((receivedElementsMatrix[row + 1][column] != 1) && (basePathMatrix[row + 1][column] == 0)) {
                std::cout << "south" << std::endl;
                if (receivedElementsMatrix[row + 1][column] == 2) {
                    std::cout << "S SUCCESS" << std::endl;
                    basePathMatrix[row + 1][column] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row + 1, column};
                    if (recursivePathing(newInitialPoint)) {
                        return true;
                    }
                }
            }
        }
        //northwest movement
        if (((row - 1 < 7)&&(0 <= row - 1)) && ((column - 1 < 9)&&(0 <= column - 1))) {
            if ((receivedElementsMatrix[row - 1][column - 1] != 1) && (basePathMatrix[row - 1][column - 1] == 0)) {
                std::cout << "northwest" << std::endl;
                if (receivedElementsMatrix[row - 1][column - 1] == 2) {
                    std::cout << "NW SUCCESS" << std::endl;
                    basePathMatrix[row - 1][column - 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row - 1, column - 1};
                    if (recursivePathing(newInitialPoint)) {
                        return true;
                    }
                }
            }
        }
        //north movement
        if (((row - 1 < 7)&&(0 <= row - 1)) && ((column < 9)&&(0 <= column))) {
            if ((receivedElementsMatrix[row - 1][column] != 1) && (basePathMatrix[row - 1][column] == 0)) {
                std::cout << "north" << std::endl;
                if (receivedElementsMatrix[row - 1][column] == 2) {
                    std::cout << "N SUCCESS" << std::endl;
                    basePathMatrix[row - 1][column] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row - 1, column};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
        //southeast movement
        if (((row + 1 < 7)&&(0 <= row + 1)) && ((column + 1 < 9)&&(0 <= column + 1))) {
            if ((receivedElementsMatrix[row + 1][column + 1] != 1) && (basePathMatrix[row + 1][column + 1] == 0)) {
                std::cout << "southeast" << std::endl;
                if (receivedElementsMatrix[row + 1][column + 1] == 2) {
                    std::cout << "SE SUCCESS" << std::endl;
                    basePathMatrix[row + 1][column + 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row + 1, column + 1};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
        // northeast movement
        if (((row - 1 < 7)&&(0 <= row - 1)) && ((column + 1 < 9)&&(0 <= column + 1))) {
            if ((receivedElementsMatrix[row - 1][column + 1] != 1) && (basePathMatrix[row - 1][column + 1] == 0)) {
                std::cout << "northeast" << std::endl;
                if (receivedElementsMatrix[row - 1][column + 1] == 2) {
                    std::cout << "NE SUCCESS" << std::endl;
                    basePathMatrix[row - 1][column + 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row - 1, column + 1};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
    } else {
        //northwest movement
        if (((row - 1 < 7)&&(0 <= row - 1)) && ((column - 1 < 9)&&(0 <= column - 1))) {
            if ((receivedElementsMatrix[row - 1][column - 1] != 1) && (basePathMatrix[row - 1][column - 1] == 0)) {
                std::cout << "northwest" << std::endl;
                if (receivedElementsMatrix[row - 1][column - 1] == 2) {
                    std::cout << "NW SUCCESS" << std::endl;
                    basePathMatrix[row - 1][column - 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row - 1, column - 1};
                    if (recursivePathing(newInitialPoint)) {
                        return true;
                    }
                }
            }
        }
        //north movement
        if (((row - 1 < 7)&&(0 <= row - 1)) && ((column < 9)&&(0 <= column))) {
            if ((receivedElementsMatrix[row - 1][column] != 1) && (basePathMatrix[row - 1][column] == 0)) {
                std::cout << "north" << std::endl;
                if (receivedElementsMatrix[row - 1][column] == 2) {
                    std::cout << "N SUCCESS" << std::endl;
                    basePathMatrix[row - 1][column] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row - 1, column};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
        //southwest movement
        if (((row + 1 < 7)&&(0 <= row + 1)) && ((column - 1 < 9)&&(0 <= column - 1))) {
            if ((receivedElementsMatrix[row + 1][column - 1] != 1) && (basePathMatrix[row + 1][column - 1] == 0)) {
                std::cout << "southwest" << std::endl;
                if (receivedElementsMatrix[row + 1][column - 1] == 2) {
                    std::cout << "SW SUCCESS" << std::endl;
                    basePathMatrix[row + 1][column - 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row + 1, column - 1};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
        //south movement
        if (((row + 1 < 7)&&(0 <= row + 1)) && ((column < 9)&&(0 <= column))) {
            if ((receivedElementsMatrix[row + 1][column] != 1) && (basePathMatrix[row + 1][column] == 0)) {
                std::cout << "south" << std::endl;
                if (receivedElementsMatrix[row + 1][column] == 2) {
                    std::cout << "S SUCCESS" << std::endl;
                    basePathMatrix[row + 1][column] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row + 1, column};
                    if (recursivePathing(newInitialPoint)) {
                        return true;
                    }
                }
            }
        }
        // northeast movement
        if (((row - 1 < 7)&&(0 <= row - 1)) && ((column + 1 < 9)&&(0 <= column + 1))) {
            if ((receivedElementsMatrix[row - 1][column + 1] != 1) && (basePathMatrix[row - 1][column + 1] == 0)) {
                std::cout << "northeast" << std::endl;
                if (receivedElementsMatrix[row - 1][column + 1] == 2) {
                    std::cout << "NE SUCCESS" << std::endl;
                    basePathMatrix[row - 1][column + 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row - 1, column + 1};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
        //southeast movement
        if (((row + 1 < 7)&&(0 <= row + 1)) && ((column + 1 < 9)&&(0 <= column + 1))) {
            if ((receivedElementsMatrix[row + 1][column + 1] != 1) && (basePathMatrix[row + 1][column + 1] == 0)) {
                std::cout << "southeast" << std::endl;
                if (receivedElementsMatrix[row + 1][column + 1] == 2) {
                    std::cout << "SE SUCCESS" << std::endl;
                    basePathMatrix[row + 1][column + 1] = counterPath + 1;
                    return true;
                } else {
                    counterPath++;
                    int newInitialPoint[2] = {row + 1, column + 1};
                    if (recursivePathing(newInitialPoint)){
                        return true;
                    }
                }
            }
        }
    //east movement
    }if (((row < 7)&&(0 <= row)) && ((column + 1 < 9)&&(0 <= column + 1))) {
        if ((receivedElementsMatrix[row][column + 1] != 1) && (basePathMatrix[row][column + 1] == 0)) {
            std::cout << "east" << std::endl;
            if (receivedElementsMatrix[row][column + 1] == 2) {
                std::cout << "E SUCCESS" << std::endl;
                basePathMatrix[row][column + 1] = counterPath + 1;
                return true;
            } else {
                counterPath++;
                int newInitialPoint[2] = {row, column + 1};
                if (recursivePathing(newInitialPoint)){
                    return true;
                }
            }
        }
    }
    std::cout << "failure, going back" << std::endl;
    counterPath--;
    basePathMatrix[row][column] = 0;
    return false;
}

BacktrackingAlgorithm::BacktrackingAlgorithm() {
    basePathMatrixAssignation();
}

