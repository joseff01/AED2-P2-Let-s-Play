#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include "GeneticIndividual.h"
#include "GeneticPopulation.h"
#include "../../LinkedList/List.h"

class GeneticAlgorithm
{
private:
    GeneticPopulation *geneticPopulation;
    bool endAlgorithmFlag = false;
    int populationSize;
    int genepoolSize;
    int generationCounter = 0;
    void geneticSelection();
    // void geneticCrossover
public:
    GeneticAlgorithm();
    void executeAlgorithm(int PopulationSize, int GenepoolSize);
};

#endif // GENETICALGORITHM_H
