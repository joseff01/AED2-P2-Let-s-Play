#ifndef GENETICINDIVIDUAL_H
#define GENETICINDIVIDUAL_H
#include <random>
#include "../../LinkedList/List.h"

class GeneticIndividual
{
private:
    List<int> geneList;
    int fitnessScore;
    int genepoolSize;
public:
    int calculateFitnessScore();
    GeneticIndividual(int GenepoolSize);
    GeneticIndividual copyGeneticIndividual();
    List<int> getGeneList() const;
    void setGeneList(const List<int> &value);
    int getFitnessScore() const;
    void setFitnessScore(int value);
};

#endif // GENETICINDIVIDUAL_H
