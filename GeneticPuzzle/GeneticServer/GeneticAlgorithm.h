#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include <random>
#include "GeneticIndividual.h"
#include "GeneticPopulation.h"
#include "../../LinkedList/List.h"
#include "tinyxml2.h"

using namespace tinyxml2;

/**
 * @brief The GeneticAlgorithm class Full implementation of the genetic algorithm in charge of finding the correct genetic sequence
 */
class GeneticAlgorithm
{
private:
    /**
     * @brief geneticPopulation Population used to get the desired outocome. It stores the individuals
     */
    GeneticPopulation geneticPopulation;
    /**
     * @brief endAlgorithmFlag flag that terminates the genetic algorithm if turned true
     */
    bool endAlgorithmFlag = false;
    /**
     * @brief populationSize amout of individuals in the poipulation
     */
    int populationSize;
    /**
     * @brief genepoolSize amout of genes stored in each individual
     */
    int genepoolSize;
    /**
     * @brief generationCounter Counter of the current generation
     */
    int generationCounter = 0;
    /**
     * @brief randomDevice Random seed to generate random values. Paired with the mt19937 engine
     */
    std::random_device randomDevice;
    /**
     * @brief mt Engine in charge of generating random numbers. Paired with the randomDevice seed.
     */
    std::mt19937 mt = std::mt19937(randomDevice());
    void showGeneration();
    void geneticSelection();
    void geneticCrossover();
    void geneticMutation();
    bool checkFinalization();
    void generateGenerationXML();

public:
    GeneticAlgorithm(int PopulationSize, int GenepoolSize);
    void executeAlgorithm();
};

#endif // GENETICALGORITHM_H
