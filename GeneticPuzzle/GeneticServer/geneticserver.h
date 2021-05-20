#ifndef GENETICSERVER_H
#define GENETICSERVER_H


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
};

#endif // GENETICSERVER_H
