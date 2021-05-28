#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int PopulationSize, int GenepoolSize): geneticPopulation(PopulationSize,GenepoolSize){
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
        std::cout<< "Crossover..." << std::endl;
        geneticCrossover();
        std::cout<< "Mutation..." << std::endl;
        geneticMutation();
        std::cout<< "Checking success..." << std::endl;
        endAlgorithmFlag = checkFinalization();
        //create xml of Geneneration
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
    std::cout<< "parents:" << std::endl;
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = chosenParents[i].getGeneList();
        std::cout << geneList << " ";
    }
    std::cout << std::endl;
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
        std::cout<< crossoverPoint << std::endl;
        std::cout<< geneListParent1 << std::endl;
        std::cout<< geneListParent2 << std::endl;
        GeneticIndividual crossedChild1 = GeneticIndividual(genepoolSize);
        GeneticIndividual crossedChild2 = GeneticIndividual(genepoolSize);
        crossedChild1.setGeneList(geneListParent1);
        crossedChild2.setGeneList(geneListParent2);
        childrenList.push_back(crossedChild1);
        childrenList.push_back(crossedChild2);
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
        std::cout<< crossoverPoint << std::endl;
        std::cout<< geneListParent1 << std::endl;
        std::cout<< geneListParent2 << std::endl;
        GeneticIndividual crossedChild1 = GeneticIndividual(genepoolSize);
        GeneticIndividual crossedChild2 = GeneticIndividual(genepoolSize);
        crossedChild1.setGeneList(geneListParent1);
        crossedChild2.setGeneList(geneListParent2);
        childrenList.push_back(crossedChild1);
        childrenList.push_back(crossedChild2);
    }
    geneticPopulation.setIndividualsList(childrenList);
    std::cout<< "crossed over children: " << std::endl;
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        std::cout << geneList << " ";
    }
    std::cout<< std::endl;
}

void GeneticAlgorithm::geneticMutation(){
    std::uniform_int_distribution<int> distGenes(0,genepoolSize-1);
    std::uniform_int_distribution<int> distMutation(1,20);
    List<GeneticIndividual> childrenList = List<GeneticIndividual>();
    for (int i = 0; i < populationSize; i++) {
        GeneticIndividual mutatedChild = GeneticIndividual(genepoolSize);
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        for (int j = 0; j < genepoolSize; j++){
            int random0to100 = distMutation(mt);
            std::cout<< random0to100 << " ";
            if (10 == random0to100){
                int randomGene = distGenes(mt);
                std::cout<< std::endl << randomGene << std::endl;
                geneList.replace(j, randomGene);
            }

        }
        mutatedChild.setGeneList(geneList);
        childrenList.push_back(mutatedChild);
    }
    std::cout<< std::endl;
    geneticPopulation.setIndividualsList(childrenList);
    std::cout<< "mutated children: " << std::endl;
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        std::cout << geneList << " ";
    }
    std::cout << std::endl;
}

bool GeneticAlgorithm::checkFinalization(){
    List<int> desiredOutcome = List<int>();
    for (int n = 0; n < genepoolSize; n++){
        desiredOutcome.push_back(n);
    }
    std::cout << "desiredOutcome: "<< desiredOutcome << std::endl;
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        std::cout << geneList << std::endl;
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


