#include "GeneticAlgorithm.h"
/**
 * @brief GeneticAlgorithm::GeneticAlgorithm constructor of GeneticAlgorithm
 * @param PopulationSize size of the population used in the genetic algorithm
 * @param GenepoolSize amount of genes that each individual will have. It corresponds to the amount of pieces that the image was divided by
 */
GeneticAlgorithm::GeneticAlgorithm(int PopulationSize, int GenepoolSize): geneticPopulation(PopulationSize,GenepoolSize){
    populationSize = PopulationSize;
    genepoolSize = GenepoolSize;
}

/**
 * @brief GeneticAlgorithm::executeAlgorithm Main algorithm in charge of executiong the entire genetic algorithm.
 */
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
/**
 * @brief GeneticAlgorithm::showGeneration Displays on console the current entire generation of individuals
 */
void GeneticAlgorithm::showGeneration()
{
    for (int i = 0; i < populationSize; i++){
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        std::cout << geneList << " ";
    }
    std::cout << std::endl;
}
/**
 * @brief GeneticAlgorithm::geneticSelection Selection algorithm in charge of selecting the parents.
 * It uses the fitness proportionate selection (FPS) to find which parents to use.
 */
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

    std::cout << std::endl;
    geneticPopulation.setIndividualsList(chosenParents);
    showGeneration();
}
/**
 * @brief GeneticAlgorithm::geneticCrossover Crossover algorithm that mixes the parents selected by geneticSelection().
 * It does this by finding a random point in each pair of parents and exchanging their genes before that point.
 */
void GeneticAlgorithm::geneticCrossover(){
    //Empty list to store the mixed children
    List<GeneticIndividual> childrenList = List<GeneticIndividual>();
    //generation of random ditribution from 0 to the genepool-1
    std::uniform_int_distribution<int> dist(0,genepoolSize-1);
    for (int i = 0; i < populationSize; i = i + 2) {
        //Getting a pair of parents
        List<int> geneListParent1 = geneticPopulation.getIndividualsList()[i].getGeneList();
        List<int> geneListParent2 = geneticPopulation.getIndividualsList()[i+1].getGeneList();
        //Random point using the distribution and the mt engine
        int crossoverPoint = dist(mt);
        //loop to exchange genes
        for (int j = 0; j < crossoverPoint; j++){
            List<int> geneListParent1Copy = geneListParent1;
            geneListParent1.replace(j, geneListParent2[j]);
            geneListParent2.replace(j, geneListParent1Copy[j]);
        }
        std::cout<< crossoverPoint << std::endl;
        std::cout<< geneListParent1 << std::endl;
        std::cout<< geneListParent2 << std::endl;
        //creating a pair of empty individuals to store the gene lists
        GeneticIndividual crossedChild1 = GeneticIndividual(genepoolSize);
        GeneticIndividual crossedChild2 = GeneticIndividual(genepoolSize);
        //setting the genelists to the newly made individuals
        crossedChild1.setGeneList(geneListParent1);
        crossedChild2.setGeneList(geneListParent2);
        //adding the new crossed children to the list of children
        childrenList.push_back(crossedChild1);
        childrenList.push_back(crossedChild2);
    }
    //Case if the population size is an odd number. Same thing as before, but exchanging between the last and the first parents and only storing the first child
    if (populationSize % 2 == 1){
        List<int> geneListParent1 = geneticPopulation.getIndividualsList()[populationSize-1].getGeneList();
        List<int> geneListParent2 = geneticPopulation.getIndividualsList()[0].getGeneList();
        int crossoverPoint = dist(mt);
        for (int j = 0; j < crossoverPoint; j++){
            geneListParent1.replace(j, geneListParent2[j]);
        }
        std::cout<< crossoverPoint << std::endl;
        std::cout<< geneListParent1 << std::endl;
        GeneticIndividual crossedChild1 = GeneticIndividual(genepoolSize);
        crossedChild1.setGeneList(geneListParent1);
        childrenList.push_back(crossedChild1);
    }
    //setting the newly made list of crossed children as the new population
    geneticPopulation.setIndividualsList(childrenList);
    std::cout<< "crossed over children: " << std::endl;
    showGeneration();
    std::cout<< std::endl;
}
/**
 * @brief GeneticAlgorithm::geneticMutation Mutation algorithm in charge of mutating 5% of the time each gene from an individual
 */
void GeneticAlgorithm::geneticMutation(){
    //random distribution of genes
    std::uniform_int_distribution<int> distGenes(0,genepoolSize-1);
    //random distribution to ensure a 5% mutation rate
    std::uniform_int_distribution<int> distMutation(1,20);
    //list of empty children to store the mutated individuals
    List<GeneticIndividual> childrenList = List<GeneticIndividual>();
    //loop of each individual
    for (int i = 0; i < populationSize; i++) {
        //creates an empty individual to store the mutated genelist
        GeneticIndividual mutatedChild = GeneticIndividual(genepoolSize);
        //genelist of individual to mutate
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        //loop of each gene in the genelist
        for (int j = 0; j < genepoolSize; j++){
            //random int between 1 and 20
            int randomMutationRate = distMutation(mt);
            std::cout<< randomMutationRate << " ";
            //if the number is a 10, it will mutate
            if (10 == randomMutationRate){
                //random gene
                int randomGene = distGenes(mt);
                std::cout<< std::endl << randomGene << std::endl;
                //replacing the old gene for the mutated one
                geneList.replace(j, randomGene);
            }

        }
        //seting the mutated genelist on the empty child
        mutatedChild.setGeneList(geneList);
        //adding said children to the list of mutated children
        childrenList.push_back(mutatedChild);
    }
    std::cout<< std::endl;
    //setting the new mutated children list as the main population
    geneticPopulation.setIndividualsList(childrenList);
    std::cout<< "mutated children: " << std::endl;
    showGeneration();

}
/**
 * @brief GeneticAlgorithm::checkFinalization Function in charge of checking if the desired genelist was created
 * @return boolean value. Returns true if an individual matches the desired outcome and false if none do.
 */
bool GeneticAlgorithm::checkFinalization(){
    //creation of the desired genelist
    List<int> desiredOutcome = List<int>();
    for (int n = 0; n < genepoolSize; n++){
        desiredOutcome.push_back(n);
    }
    std::cout << "desiredOutcome: "<< desiredOutcome << std::endl;
    //loop for each current individual
    for (int i = 0; i < populationSize; i++){
        //loop for each gene in a genelist of an individual
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        std::cout << geneList << std::endl;
        for (int j = 0; j < genepoolSize; j++){
            //if it goes through all genes without exiting, it means it found the correct genelist
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
/*
void GeneticAlgorithm::generateGenerationXML()
{
    XMLDocument xmlDoc;
    XMLNode *pRoot = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(pRoot);
    XMLElement *pElement = xmlDoc.NewElement("Generations");

}
*/

