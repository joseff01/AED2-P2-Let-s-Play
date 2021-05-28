#include "GeneticIndividual.h"

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

int GeneticIndividual::calculateFitnessScore()
{
    fitnessScore = 0;
    for (int i = 0; i < genepoolSize; i++){
        if (geneList[i] == i){
            fitnessScore++;
        }
    }
    return fitnessScore;
}

GeneticIndividual GeneticIndividual::copyGeneticIndividual(){
        GeneticIndividual copyIndividual = GeneticIndividual(genepoolSize);
        copyIndividual.setFitnessScore(fitnessScore);
        copyIndividual.setGeneList(geneList);
        return copyIndividual;
}

List<int> GeneticIndividual::getGeneList() const
{
    return geneList;
}

void GeneticIndividual::setGeneList(const List<int> &value)
{
    geneList = value;
    calculateFitnessScore();
}

int GeneticIndividual::getFitnessScore() const
{
    return fitnessScore;
}
