#include "GeneticServer.h"
#include "GeneticAlgorithm.h"
#include <iostream>

int main()
{
    /*
    GeneticServer *geneticServer = new GeneticServer();
    delete (geneticServer); //Para que Qt deje de llorar por memory leaks
    */
    List<int> l = List<int>();
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    List<int> p = List<int>();
    p.push_back(7);
    p.push_back(8);
    p.push_back(9);
    p.push_back(10);
    p.push_back(11);
    p.push_back(12);
    l = p;
    std::cout << l << std::endl;
    std::cout << l.length() << std::endl;
    /*GeneticAlgorithm geneticAlgorithm(6,8);
    geneticAlgorithm.executeAlgorithm();
    */
}
