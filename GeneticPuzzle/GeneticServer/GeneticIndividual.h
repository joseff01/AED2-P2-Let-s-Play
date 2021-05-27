#ifndef GENETICINDIVIDUAL_H
#define GENETICINDIVIDUAL_H
#include "../../LinkedList/List.h"

class GeneticIndividual
{
private:
    List<int> *geneList;
    int fitnessScore;
    int genepoolSize;
public:
    int calculateFitnessScore();
    GeneticIndividual(int GenepoolSize);
    List<int> *getGeneList() const;
};

#endif // GENETICINDIVIDUAL_H
