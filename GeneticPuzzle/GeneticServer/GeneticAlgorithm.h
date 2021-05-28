#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include <random>
#include "GeneticIndividual.h"
#include "GeneticPopulation.h"
#include "../../LinkedList/List.h"

class GeneticAlgorithm
{
private:
    GeneticPopulation geneticPopulation;
    bool endAlgorithmFlag = false;
    int populationSize;
    int genepoolSize;
    int generationCounter = 0;
    std::random_device randomDevice;
    std::mt19937 mt = std::mt19937(randomDevice());
    void showGeneration();
    void geneticSelection();
    void geneticCrossover();
    void geneticMutation();
    bool checkFinalization();

public:
    GeneticAlgorithm(int PopulationSize, int GenepoolSize);
    void executeAlgorithm();
};

#endif // GENETICALGORITHM_H
