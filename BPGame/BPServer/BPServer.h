#ifndef BPSERVER_BPSERVER_H
#define BPSERVER_BPSERVER_H
#include "json.hpp"
#include "../../LinkedList/List.h"

using json = nlohmann::json;

class BPServer
{
private:
    int baseSocketNumber = 5000;
    int sockfd{}, newsockfd{};
    char buffer[2048]{};
    void error(const char *msg);
    void bindingProcess(int *sockfd, int *portno, struct sockaddr_in *serv_addr);
    void serverSetup();

public:
    BPServer();
    void readBuffer();
    json getBuffer();
    void sendBuffer(json jsonMsg);
    void endServer();
    List<List<int>> fixMatrix(List<List<int>> badMatrix);
};

#endif //BPSERVER_BPSERVER_H
