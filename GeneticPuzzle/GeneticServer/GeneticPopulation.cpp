#include "GeneticPopulation.h"

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

int GeneticPopulation::sumOfFitnesses()
{
    int fitnessesSum = 0;
    for (int i = 0; i < populationSize; i++){
        GeneticIndividual individual = individualsList[i];
        fitnessesSum = fitnessesSum + individual.getFitnessScore();
    }
    return fitnessesSum;
}

List<GeneticIndividual> GeneticPopulation::getIndividualsList() const
{
    return individualsList;
}

void GeneticPopulation::setIndividualsList(const List<GeneticIndividual> &value)
{
    individualsList = value;
}

