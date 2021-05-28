#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int PopulationSize, int GenepoolSize): geneticPopulation(PopulationSize,GenepoolSize){
    populationSize = PopulationSize;
    genepoolSize = GenepoolSize;
}


void GeneticAlgorithm::executeAlgorithm(){
    generationCounter = 0;
    //create xml of Gen 0
    while(!endAlgorithmFlag){
        generationCounter++;
        geneticSelection();
        geneticCrossover();
    }
}

void GeneticAlgorithm::geneticSelection(){
    int sumOfFitness = geneticPopulation.sumOfFitnesses();
    List<float> listOfProbabilities = List<float>();
    List<GeneticIndividual> listIndividuals = geneticPopulation.getIndividualsList();
    for (int i = 0; i < populationSize; i++){
        float probability = listIndividuals[i].getFitnessScore()/sumOfFitness;
        listOfProbabilities.push_back(probability);
    }
    List<GeneticIndividual> chosenParents = List<GeneticIndividual>();
    std::uniform_real_distribution<float> dist(0,1);
    float probabilitySum = 0;
    while(chosenParents.length() < populationSize){
        probabilitySum = 0;
        float chosenPoint = dist(mt);
        for (int j = 0; j < populationSize; j++){
            probabilitySum = probabilitySum + listOfProbabilities[j];
            if (probabilitySum > chosenPoint){
                GeneticIndividual copyIndividual = listIndividuals[j].copyGeneticIndividual();
                chosenParents.push_back(copyIndividual);
                break;
            }
        }
    }
    geneticPopulation.setIndividualsList(chosenParents);
}

void GeneticAlgorithm::geneticCrossover(){
    List<GeneticIndividual> childrenList = List<GeneticIndividual>();
    std::uniform_int_distribution<float> dist(0,genepoolSize-1);
    for (int i = 0; i < populationSize; i = i + 2) {
        List<int> geneListParent1 = geneticPopulation.getIndividualsList()[i].getGeneList();
        List<int> geneListParent2 = geneticPopulation.getIndividualsList()[i+1].getGeneList();
        int crossoverPoint = dist(mt);
        for (int j = 0; j < crossoverPoint; j++){
            List<int> geneListParent1Copy = geneListParent1;
            geneListParent1.replace(j, geneListParent2[j]);
            geneListParent2.replace(j, geneListParent1Copy[j]);
        }
        geneticPopulation.getIndividualsList()[i].setGeneList(geneListParent1);
        geneticPopulation.getIndividualsList()[i].setGeneList(geneListParent2);
    }
    //Case if it's an odd number population size
    if (populationSize % 2 == 1){
        List<int> geneListParent1 = geneticPopulation.getIndividualsList()[populationSize-1].getGeneList();
        List<int> geneListParent2 = geneticPopulation.getIndividualsList()[0].getGeneList();
        int crossoverPoint = dist(mt);
        for (int j = 0; j < crossoverPoint; j++){
            List<int> geneListParent1Copy = geneListParent1;
            geneListParent1.replace(j, geneListParent2[j]);
            geneListParent2.replace(j, geneListParent1Copy[j]);
        }
        geneticPopulation.getIndividualsList()[populationSize-1].setGeneList(geneListParent1);
        geneticPopulation.getIndividualsList()[0].setGeneList(geneListParent2);
    }
}


