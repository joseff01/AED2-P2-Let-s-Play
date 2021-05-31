#include "GeneticServer.h"
#include "GeneticAlgorithm.h"
#include <iostream>

using namespace tinyxml2;

int main()
{
    GeneticServer geneticServer = GeneticServer();
    while (true)
    {
        geneticServer.readBuffer();
        json jsonBuffer = geneticServer.getBuffer();
        GeneticAlgorithm geneticAlgorithm(jsonBuffer["populationSize"], jsonBuffer["genepoolSize"]);
        int generations = geneticAlgorithm.executeAlgorithm(jsonBuffer["maxIterations"]);
        // return number of generations
        json generationsJSON;
        generationsJSON["generations"] = generations;
        geneticServer.sendBuffer(generationsJSON.dump());
    }
}
