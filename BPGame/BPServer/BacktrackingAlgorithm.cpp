#include "BacktrackingAlgorithm.h"
#include <iostream>
#include <cstring>

void* BacktrackingAlgorithm::findPath(int elementsMatrix[7][9]){
    int initialPoint[2];
    counterPath = 1;
    //Search for first element position AND copy the received matrix to the attribute in BacktrackingAlgorithm
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 9; j++){
            receivedElementsMatrix[i][j] = elementsMatrix[i][j];
            basePathMatrix[i][j] = 0;
            if (elementsMatrix[i][j] == 3){
                initialPoint[0] = i;
                initialPoint[1] = j;
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
    if (((row < 7)&&(0 <= row)) && ((column - 1 < 9)&&(0 <= column - 1))){
        if ((receivedElementsMatrix[row][column - 1 ] != 1) && (basePathMatrix[row][column - 1] == 0)) {
            if (receivedElementsMatrix[row][column - 1] == 2) {
                basePathMatrix[row][column - 1] = counterPath + 1;
                return true;
            } else {
                counterPath++;
                int newInitialPoint[2] = {row, column - 1};
                if (recursivePathing(newInitialPoint)){
                    return true;
                }
            }
        }
    //northwest movement
    } else if (((row - 1 < 7)&&(0 <= row - 1)) && ((column - 1 < 9)&&(0 <= column - 1))) {
        if ((receivedElementsMatrix[row - 1][column - 1] != 1) && (basePathMatrix[row - 1][column - 1] == 0)) {
            if (receivedElementsMatrix[row - 1][column - 1] == 2) {
                basePathMatrix[row - 1][column - 1] = counterPath + 1;
                return true;
            } else {
                counterPath++;
                int newInitialPoint[2] = {row - 1, column - 1};
                if (recursivePathing(newInitialPoint)){
                    return true;
                }
            }
        }
    //southeast movement
    } else if (((row + 1 < 7)&&(0 <= row + 1)) && ((column - 1 < 9)&&(0 <= column - 1))) {
        if ((receivedElementsMatrix[row + 1][column - 1] != 1) && (basePathMatrix[row + 1][column - 1] == 0)) {
            if (receivedElementsMatrix[row + 1][column - 1] == 2) {
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
    //north movement
    } else if (((row - 1 < 7)&&(0 <= row - 1)) && ((column < 9)&&(0 <= column))) {
        if ((receivedElementsMatrix[row - 1][column] != 1) && (basePathMatrix[row - 1][column] == 0)) {
            if (receivedElementsMatrix[row - 1][column] == 2) {
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
    //south movement
    } else if (((row + 1 < 7)&&(0 <= row + 1)) && ((column < 9)&&(0 <= column))) {
        if ((receivedElementsMatrix[row + 1][column] != 1) &&
            (basePathMatrix[row + 1][column] == 0)) {
            if (receivedElementsMatrix[row + 1][column] == 2) {
                basePathMatrix[row + 1][column] = counterPath + 1;
                return true;
            } else {
                counterPath++;
                int newInitialPoint[2] = {row + 1, column};
                if (recursivePathing(newInitialPoint)){
                    return true;
                }
            }
        }
    // northeast movement
    } else if (((row - 1 < 7)&&(0 <= row - 1)) && ((column + 1 < 9)&&(0 <= column + 1))) {
        if ((receivedElementsMatrix[row - 1][column + 1] != 1) && (basePathMatrix[row - 1][column + 1] == 0)) {
            if (receivedElementsMatrix[row - 1][column + 1] == 2) {
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
    //southeast movement
    } else if (((row + 1 < 7)&&(0 <= row + 1)) && ((column + 1 < 9)&&(0 <= column + 1))) {
        if ((receivedElementsMatrix[row + 1][column + 1] != 1) && (basePathMatrix[row + 1][column + 1] == 0)) {
            if (receivedElementsMatrix[row + 1][column + 1] == 2) {
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
    //east movement
    } else if (((row < 7)&&(0 <= row)) && ((column + 1 < 9)&&(0 <= column + 1))) {
        if ((receivedElementsMatrix[row][column + 1] != 1) && (basePathMatrix[row][column + 1] == 0)) {
            if (receivedElementsMatrix[row][column + 1] == 2) {
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
    } else {
        basePathMatrix[row][column] = 0;
        return false;
    }
    return false;
}

BacktrackingAlgorithm::BacktrackingAlgorithm() = default;

