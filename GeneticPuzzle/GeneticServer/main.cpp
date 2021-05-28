#include "GeneticServer.h"
#include "GeneticAlgorithm.h"
#include <iostream>

using namespace tinyxml2;

int main()
{
    /*
    GeneticServer *geneticServer = new GeneticServer();
    delete (geneticServer); //Para que Qt deje de llorar por memory leaks
    */

    GeneticAlgorithm geneticAlgorithm(10,16);
    geneticAlgorithm.removeOldXML();
    //geneticAlgorithm.executeAlgorithm(5000);

}
