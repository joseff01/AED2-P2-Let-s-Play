#include "GeneticPopulation.h"
/**
 * @brief GeneticPopulation::GeneticPopulation Constructor of the GeneticPopulation
 * @param PopulationSize size of the population used in the genetic algorithm
 * @param GenepoolSize amount of genes that each individual will have. It corresponds to the amount of pieces that the image was divided by
 */
GeneticPopulation::GeneticPopulation(int PopulationSize, int GenepoolSize)
{
    populationSize = PopulationSize;
    genepoolSize = GenepoolSize;
    individualsList = List<GeneticIndividual>();
    for (int i = 0; i < populationSize; i++){
        GeneticIndividual individual(genepoolSize);
        individualsList.push_back(individual);
    }
}
/**
 * @brief GeneticPopulation::sumOfFitnesses Function that calculates the sum of all the fitnesses of the individuals of the population
 * @return fitnessesSum Sum of all fitnesses of the individuals
 */
int GeneticPopulation::sumOfFitnesses()
{
    int fitnessesSum = 0;
    for (int i = 0; i < populationSize; i++){
        GeneticIndividual individual = individualsList[i];
        fitnessesSum = fitnessesSum + individual.getFitnessScore();
    }
    return fitnessesSum;
}
/**
 * @brief GeneticPopulation::getIndividualsList Getter of the list of individuals that are currently a part of the population
 * @return individualsList List of individuals in the population
 */
List<GeneticIndividual> GeneticPopulation::getIndividualsList() const
{
    return individualsList;
}
/**
 * @brief GeneticPopulation::setIndividualsList Setter of the list of individuals that are currently a part of the population
 * @param value List of individuals in the population
 */
void GeneticPopulation::setIndividualsList(const List<GeneticIndividual> &value)
{
    individualsList = value;
}

