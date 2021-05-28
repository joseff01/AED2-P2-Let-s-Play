#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int PopulationSize, int GenepoolSize): geneticPopulation(PopulationSize,GenepoolSize){
    desiredOutcome = List<int>();
    for (int i = 0; i < genepoolSize; i++){
        desiredOutcome.push_back(i);
    }
    populationSize = PopulationSize;
    genepoolSize = GenepoolSize;
}


void GeneticAlgorithm::executeAlgorithm(){
    generationCounter = 0;
    //create xml of Gen 0
    while(!endAlgorithmFlag){
        showGeneration();
        generationCounter++;
        std::cout<< "Selecting parents..." << std::endl;
        geneticSelection();
        /*std::cout<< "Crossover..." << std::endl;
        geneticCrossover();
        std::cout<< "Mutation..." << std::endl;
        geneticMutation();
        //create xml of Geneneration
        if (checkFinalization()){
            endAlgorithmFlag = true;
        }
        */
        break;
    }
}

void GeneticAlgorithm::showGeneration()
{
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        std::cout << geneList << " ";
    }
    std::cout << std::endl;
}

void GeneticAlgorithm::geneticSelection(){
    std::cout<< "calculating sumOfFitness..." << std::endl;
    int sumOfFitness = geneticPopulation.sumOfFitnesses();
    std::cout<< "sumOfFitness: " << sumOfFitness << std::endl;
    List<float> listOfProbabilities = List<float>();
    List<GeneticIndividual> listIndividuals = geneticPopulation.getIndividualsList();
    std::cout<< "calculating probabilities..." << std::endl;
    for (int i = 0; i < populationSize; i++){
        float probability = (float)listIndividuals[i].getFitnessScore()/(float)sumOfFitness;
        listOfProbabilities.push_back(probability);
    }
    std::cout<< "probabilities: " << listOfProbabilities << std::endl;
    List<GeneticIndividual> chosenParents = List<GeneticIndividual>();
    std::uniform_real_distribution<float> dist(0,1);
    float probabilitySum = 0;
    std::cout<< "selecting parents..."<< std::endl;
    while(chosenParents.length() < (populationSize)){
        probabilitySum = 0;
        float chosenPoint = dist(mt);
        std::cout<< "chosenPoint: " << chosenPoint << std::endl;
        for (int j = 0; j < populationSize; j++){
            probabilitySum = probabilitySum + listOfProbabilities[j];
            if (probabilitySum > chosenPoint){
                GeneticIndividual copyIndividual = GeneticIndividual(genepoolSize);
                copyIndividual.setGeneList(listIndividuals[j].getGeneList());
                chosenParents.push_back(copyIndividual);
                break;
            }
        }
    }
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = chosenParents[i].getGeneList();
        std::cout << geneList << " ";
    }
    std::cout << std::endl;
    std::cout<< "parents:" << std::endl;

    geneticPopulation.setIndividualsList(chosenParents);
}

void GeneticAlgorithm::geneticCrossover(){
    List<GeneticIndividual> childrenList = List<GeneticIndividual>();
    std::uniform_int_distribution<int> dist(0,genepoolSize-1);
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

void GeneticAlgorithm::geneticMutation(){
    std::uniform_int_distribution<int> distGenes(0,genepoolSize-1);
    std::uniform_int_distribution<int> distMutation(1,100);
    List<GeneticIndividual> childrenList = geneticPopulation.getIndividualsList();
    for (int i = 0; i < populationSize; i++) {
        List<int> geneList = childrenList[i].getGeneList();
        for (int j = 0; j < genepoolSize; j++){
            if (50 == distMutation(mt)){
                geneList.replace(j, distGenes(mt));
            }
        }
        childrenList[i].setGeneList(geneList);
    }
    geneticPopulation.setIndividualsList(childrenList);
}

bool GeneticAlgorithm::checkFinalization()
{
    List<GeneticIndividual> childrenList = geneticPopulation.getIndividualsList();
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = childrenList[i].getGeneList();
        for (int j = 0; j < genepoolSize; j++){
            if (j == genepoolSize-1){
                return true;
            } else if (desiredOutcome[j] == geneList[j]){
                continue;
            } else{
                break;
            }
        }
    }
    return false;
}


