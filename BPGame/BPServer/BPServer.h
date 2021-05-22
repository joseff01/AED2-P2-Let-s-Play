#ifndef BPSERVER_BPSERVER_H
#define BPSERVER_BPSERVER_H

class BPServer{
private:
    int baseSocketNumber = 5000;
    int sockfd{}, newsockfd{};
    char buffer[511]{};
    void error(const char *msg);
    void bindingProcess(int* sockfd, int* portno, struct sockaddr_in* serv_addr);
    void serverSetup();

public:
    BPServer();
};



#endif //BPSERVER_BPSERVER_H
