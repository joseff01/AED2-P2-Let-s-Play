#include "GeneticServer.h"
#include "GeneticAlgorithm.h"
#include <iostream>

using namespace tinyxml2;

int main()
{
    GeneticServer geneticServer = GeneticServer();
    while(true){
        geneticServer.readBuffer();
        json jsonBuffer = geneticServer.getBuffer();
        GeneticAlgorithm geneticAlgorithm(jsonBuffer["populationSize"],jsonBuffer["genepoolSize"]);
        geneticAlgorithm.executeAlgorithm(jsonBuffer["maxIterations"]);
        geneticServer.sendBuffer("Done");
    }
}
