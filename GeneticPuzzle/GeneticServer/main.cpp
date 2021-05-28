#include "GeneticServer.h"
#include "GeneticAlgorithm.h"
#include <iostream>

int main()
{
    /*
    GeneticServer *geneticServer = new GeneticServer();
    delete (geneticServer); //Para que Qt deje de llorar por memory leaks
    */


    GeneticAlgorithm geneticAlgorithm(10,8);
    geneticAlgorithm.executeAlgorithm();
}
