#ifndef GENETICPOPULATION_H
#define GENETICPOPULATION_H
#include "GeneticIndividual.h"

class GeneticPopulation
{
private:
    int populationSize;
    int genepoolSize;
    List<GeneticIndividual> individualsList;

public:
    GeneticPopulation(int PopulationSize, int GenepoolSize);
    int sumOfFitnesses();
    //GeneticIndividual getFittestsIndividuals();
    List<GeneticIndividual> getIndividualsList() const;
    void setIndividualsList(const List<GeneticIndividual> &value);
};

#endif // GENETICPOPULATION_H
