#include "GeneticPopulation.h"

GeneticPopulation::GeneticPopulation(int PopulationSize, int GenepoolSize)
{
    populationSize = PopulationSize;
    genepoolSize = GenepoolSize;
    individualsList = new List<GeneticIndividual>();
    for (int i = 0; i < populationSize; i++){
        GeneticIndividual individual(genepoolSize);
        individualsList->push_back(individual);
    }
}
