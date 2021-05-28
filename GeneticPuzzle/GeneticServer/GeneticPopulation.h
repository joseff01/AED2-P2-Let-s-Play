#ifndef GENETICPOPULATION_H
#define GENETICPOPULATION_H
#include "GeneticIndividual.h"

class GeneticPopulation
{
private:
    /**
     * @brief populationSize amout of individuals in the poipulation
     */
    int populationSize;
    /**
     * @brief genepoolSize amout of genes stored in each individual
     */
    int genepoolSize;
    /**
     * @brief individualsList List of all individuals stored in the population
     */
    List<GeneticIndividual> individualsList;

public:
    GeneticPopulation(int PopulationSize, int GenepoolSize);
    int sumOfFitnesses();
    //GeneticIndividual getFittestsIndividuals();
    List<GeneticIndividual> getIndividualsList() const;
    void setIndividualsList(const List<GeneticIndividual> &value);
};

#endif // GENETICPOPULATION_H
