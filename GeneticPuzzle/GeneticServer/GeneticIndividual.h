#ifndef GENETICINDIVIDUAL_H
#define GENETICINDIVIDUAL_H
#include <random>
#include "../../LinkedList/List.h"
/**
 * @brief The GeneticIndividual class A single individual of the Population used for the genetic algorithm. Stores a genetic list.
 */
class GeneticIndividual
{
private:
    /**
     * @brief geneList List of genes contained in the individual
     */
    List<int> geneList;
    /**
     * @brief fitnessScore Score that shows how close the individual's genes are compared to the desired ones.
     */
    int fitnessScore;
    /**
     * @brief genepoolSize amout of genes stored in each individual
     */
    int genepoolSize;
public:
    int calculateFitnessScore();
    GeneticIndividual(int GenepoolSize);
    GeneticIndividual copyGeneticIndividual();
    List<int> getGeneList() const;
    void setGeneList(List<int> value);
    int getFitnessScore() const;
    void setFitnessScore(int value);
};

#endif // GENETICINDIVIDUAL_H
