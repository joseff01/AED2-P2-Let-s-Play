#include <geneticserver.h>
#include <iostream>


int main(){
    GeneticServer* geneticServer = new GeneticServer();
    delete(geneticServer); //Para que Qt deje de llorar por memory leaks
}

