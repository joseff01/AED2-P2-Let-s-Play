#ifndef GENETICSERVER_H
#define GENETICSERVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;

class GeneticServer
{
private:
    int baseSocketNumber = 5000;
    int sockfd, newsockfd;
    char buffer[511];
    void error(const char *msg);
    void bindingProcess(int* sockfd, int* portno, struct sockaddr_in* serv_addr);
    void serverSetup();

public:
    GeneticServer();
    void readBuffer();
    json getBuffer();
    void sendBuffer(std::string Msg);
};

#endif // GENETICSERVER_H
