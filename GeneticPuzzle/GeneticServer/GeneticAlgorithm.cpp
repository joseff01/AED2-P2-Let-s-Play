#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

void GeneticAlgorithm::executeAlgorithm(int PopulationSize, int GenepoolSize){
    populationSize = PopulationSize;
    genepoolSize = GenepoolSize;
    geneticPopulation = new GeneticPopulation(populationSize,genepoolSize);
    generationCounter = 0;
    //create xml of Gen 0
    while(!endAlgorithmFlag){
        generationCounter++;
        geneticSelection();
    }
}

void GeneticAlgorithm::geneticSelection(){
    //float sumOfFitnesses =
    List<float> listOfProbabilities = List<float>();
    for (int j = 0; j < populationSize; j++){
        listOfProbabilities.push_back();
    }
}
