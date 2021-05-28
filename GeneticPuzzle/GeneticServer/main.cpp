#include "GeneticServer.h"
#include "GeneticAlgorithm.h"
#include "tinyxml2.h"
#include <iostream>
#ifndef XMLCheckResult
    #define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif
int main()
{
    /*
    GeneticServer *geneticServer = new GeneticServer();
    delete (geneticServer); //Para que Qt deje de llorar por memory leaks
    */
    /*
    std::cout << "hola" << std::endl;
    List<int> l = {0,1,2,3,4,5,6};
    XMLDocument xmlDoc;
    XMLNode *pRoot = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(pRoot);

    XMLElement *pElement = xmlDoc.NewElement("Generations");

    for (int i = 0; i < 7; i++){
        XMLElement *pListElement = xmlDoc.NewElement("item");
        pListElement->SetText("l[i]");

        pElement->InsertEndChild(pListElement);
    }
    pRoot->InsertEndChild(pElement);

    const char *path = "mecagoenMilton.xml";
    XMLError eResult = xmlDoc.SaveFile(path);
    XMLCheckResult(eResult);
    */


    /*
    GeneticAlgorithm geneticAlgorithm(10,8);
    geneticAlgorithm.executeAlgorithm();
    */
}
