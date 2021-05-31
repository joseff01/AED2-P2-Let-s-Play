#include "GeneticIndividual.h"
/**
 * @brief GeneticIndividual::GeneticIndividual Constructor of GeneticIndividual.
 * @param GenepoolSize Amount of genes to store in each individual
 */
GeneticIndividual::GeneticIndividual(int GenepoolSize)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    genepoolSize = GenepoolSize;
    std::uniform_int_distribution<int> dist(0,genepoolSize-1);
    geneList = List<int>();
    for (int i = 0; i < genepoolSize; i++){
        geneList.push_back(dist(mt));
    }
    calculateFitnessScore();
}
/**
 * @brief GeneticIndividual::calculateFitnessScore function in charge of calculating the fitness score of the individual
 * It does so by adding 1 to it's fitness for each matching gene
 * @return returns the fitness score calculated
 */
int GeneticIndividual::calculateFitnessScore()
{
    fitnessScore = 1;
    for (int i = 0; i < genepoolSize; i++){
        if (geneList[i] == i){
            fitnessScore++;
        }
    }
    return fitnessScore;
}

/**
 * @brief GeneticIndividual::copyGeneticIndividual Function that copies the individual and returns a Deep copy of it
 * @return copyIndividual the new deep copy of the individual
 */
GeneticIndividual GeneticIndividual::copyGeneticIndividual(){
        GeneticIndividual copyIndividual = GeneticIndividual(genepoolSize);
        copyIndividual.setFitnessScore(fitnessScore);
        copyIndividual.setGeneList(geneList);
        return copyIndividual;
}
/**
 * @brief GeneticIndividual::getGeneList Getter of the genelist
 * @return geneList genelist currently stored in the genelist
 */
List<int> GeneticIndividual::getGeneList() const
{
    return geneList;
}
/**
 * @brief GeneticIndividual::setGeneList Setter of the genelist
 * @param value genelist to save in the individual
 */
void GeneticIndividual::setGeneList(List<int> value)
{
    geneList = value;
    calculateFitnessScore();
}
/**
 * @brief GeneticIndividual::getFitnessScore Getter of the fitnesscore of the individual
 * @return fitnessScore fitness score of the individual
 */
int GeneticIndividual::getFitnessScore() const
{
    return fitnessScore;
}
/**
 * @brief GeneticIndividual::setFitnessScore Setter of the fitnessScore
 * @param value fitnessScore to save in the individual
 */
void GeneticIndividual::setFitnessScore(int value)
{
    fitnessScore = value;
}
