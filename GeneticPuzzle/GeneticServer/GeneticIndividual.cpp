#include <stdlib.h>
#include "GeneticIndividual.h"

GeneticIndividual::GeneticIndividual(int GenepoolSize)
{
    genepoolSize = GenepoolSize;
    geneList = new List<int>();
    for (int i = 0; i < genepoolSize; i++){
        geneList->push_back(rand() % genepoolSize);
    }
    calculateFitnessScore();
}

int GeneticIndividual::calculateFitnessScore()
{
    fitnessScore = 0;
    for (int i = 0; i < genepoolSize; i++){
        if (geneList->at(i) == i){
            fitnessScore++;
        }
    }
    return fitnessScore;
}

List<int> *GeneticIndividual::getGeneList() const
{
    return geneList;
}
