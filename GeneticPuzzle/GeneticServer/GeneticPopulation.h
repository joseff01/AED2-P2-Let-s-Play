#ifndef GENETICPOPULATION_H
#define GENETICPOPULATION_H
#include "GeneticIndividual.h"

class GeneticPopulation
{
private:
    int populationSize;
    int genepoolSize;
    List<GeneticIndividual> *individualsList;

public:
    GeneticPopulation(int PopulationSize, int GenepoolSize);
    //GeneticIndividual getFittestsIndividuals();
};

#endif // GENETICPOPULATION_H
