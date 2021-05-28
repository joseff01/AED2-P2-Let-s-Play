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
 * @param maxIterations Max allowed iterations of the algorithm
 */
void GeneticAlgorithm::executeAlgorithm(int maxIterations){
    removeOldXML();
    generationCounter = 0;
    generateGenerationXML();
    while(!endAlgorithmFlag){
        if (maxIterations == generationCounter){
            return;
        }
        showGeneration();
        generationCounter++;
        //std::cout<< "Selecting parents..." << std::endl;
        geneticSelection();
        //std::cout<< "Crossover..." << std::endl;
        geneticCrossover();
        //std::cout<< "Mutation..." << std::endl;
        geneticMutation();
        //std::cout<< "Checking success..." << std::endl;
        generateGenerationXML();
        endAlgorithmFlag = checkFinalization();
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
    //std::cout<< "calculating sumOfFitness..." << std::endl;
    int sumOfFitness = geneticPopulation.sumOfFitnesses();
    //std::cout<< "sumOfFitness: " << sumOfFitness << std::endl;
    List<float> listOfProbabilities = List<float>();
    List<GeneticIndividual> listIndividuals = geneticPopulation.getIndividualsList();
    //std::cout<< "calculating probabilities..." << std::endl;
    for (int i = 0; i < populationSize; i++){
        float probability = (float)listIndividuals[i].getFitnessScore()/(float)sumOfFitness;
        listOfProbabilities.push_back(probability);
    }
    //std::cout<< "probabilities: " << listOfProbabilities << std::endl;
    List<GeneticIndividual> chosenParents = List<GeneticIndividual>();
    std::uniform_real_distribution<float> dist(0,1);
    float probabilitySum = 0;
    //std::cout<< "selecting parents..."<< std::endl;
    while(chosenParents.length() < (populationSize)){
        probabilitySum = 0;
        float chosenPoint = dist(mt);
        //std::cout<< "chosenPoint: " << chosenPoint << std::endl;
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
    //std::cout<< "parents:" << std::endl;

    //std::cout << std::endl;
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
        //std::cout<< crossoverPoint << std::endl;
        //std::cout<< geneListParent1 << std::endl;
        //std::cout<< geneListParent2 << std::endl;
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
    //std::cout<< "crossed over children: " << std::endl;
    showGeneration();
    //std::cout<< std::endl;
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
            //std::cout<< randomMutationRate << " ";
            //if the number is a 10, it will mutate
            if (10 == randomMutationRate){
                //random gene
                int randomGene = distGenes(mt);
                //std::cout<< std::endl << randomGene << std::endl;
                //replacing the old gene for the mutated one
                geneList.replace(j, randomGene);
            }

        }
        //seting the mutated genelist on the empty child
        mutatedChild.setGeneList(geneList);
        //adding said children to the list of mutated children
        childrenList.push_back(mutatedChild);
    }
    //std::cout<< std::endl;
    //setting the new mutated children list as the main population
    geneticPopulation.setIndividualsList(childrenList);
    //std::cout<< "mutated children: " << std::endl;
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
    //std::cout << "desiredOutcome: "<< desiredOutcome << std::endl;
    //loop for each current individual
    for (int i = 0; i < populationSize; i++){
        //loop for each gene in a genelist of an individual
        List<int> geneList = geneticPopulation.getIndividualsList()[i].getGeneList();
        //std::cout << geneList << std::endl;
        for (int j = 0; j < genepoolSize; j++){
            //if it goes through all genes without exiting, it means it found the correct genelist
            if (j == genepoolSize-1){
                if (desiredOutcome[j] == geneList[j]){
                    return true;
                } else{
                    break;
                }
            } else if (desiredOutcome[j] == geneList[j]){
                continue;
            } else{
                break;
            }
        }
    }
    return false;
}
/**
 * @brief GeneticAlgorithm::generateGenerationXML Function that creates an XML file at the GenerationXML directory that will save
 * the information about the current population/generation of individuals.(Genes and fitness values)
 */
void GeneticAlgorithm::generateGenerationXML()
{
    // Creation of xml document object
    XMLDocument xmlDoc;
    // Adding the standard Root Node to the xml document
    XMLNode *pRoot = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(pRoot);
    // Creation of the element that will contain the list of genes and the fitness of each individual
    XMLElement *pElement = xmlDoc.NewElement("Generation");
    // Getting the list of individuals
    List<GeneticIndividual> generationList = geneticPopulation.getIndividualsList();
    // Loop to get each individual into the xml document
    for (int i = 0; i < populationSize; i++){
        //Setting the number of the individual
        std::string IndividualCounterStr = std::to_string(i);
        std::string IndividualStr = "Individual";
        IndividualStr.append(IndividualCounterStr);
        const char * s = IndividualStr.c_str();
        //Creating pList element that will contain all genes of the individual
        XMLElement *pList = xmlDoc.NewElement(s);
        //Creating element with the fitness of the individual
        XMLElement *pFitness = xmlDoc.NewElement("Fitness");
        pFitness->SetText(generationList[i].getFitnessScore());
        //Inserting the fitness into the list of genes
        pList->InsertEndChild(pFitness);
        //Getting the list of genes of the individual
        List<int> geneList = generationList[i].getGeneList();
        //Loop to get each gene from the individual into the xml document
        for (int j = 0; j < genepoolSize; j++){
            //Setting the number of the gene
            std::string geneCounterStr = std::to_string(j);
            std::string geneStr = "Gene";
            geneStr.append(geneCounterStr);
            const char * n = geneStr.c_str();
            //Creating the element that will store the gene
            XMLElement *pListElement = xmlDoc.NewElement(n);
            pListElement->SetText(geneList[j]);
            //Inserting gene into the list of genes
            pList->InsertEndChild(pListElement);
        }
        pRoot->InsertEndChild(pList);
    }
    //Creation of diferent filenames depending of the current generation counter
    std::string XMLStr = "../GenerationXML/XMLGeneration";
    std::string generationCounterStr = std::to_string(generationCounter);
    XMLStr.append(generationCounterStr);
    XMLStr.append(".xml");
    const char * p = XMLStr.c_str();
    //Saving the file acording to the filepath of GenerationXML defined previously
    xmlDoc.SaveFile(p);
}
/**
 * @brief GeneticAlgorithm::removeOldXML Function that removes all previous xml files that are currently in the GenerationXML directory
 */
void GeneticAlgorithm::removeOldXML()
{
    QDir path("../GenerationXML");
    path.setNameFilters(QStringList() << "*.xml");
    path.setFilter(QDir::Files);
    foreach(QString dirfile, path.entryList()){
        path.remove(dirfile);
    }
}


