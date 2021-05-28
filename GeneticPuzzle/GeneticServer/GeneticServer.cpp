#include "GeneticServer.h"

using namespace std;

GeneticServer::GeneticServer()
{
    serverSetup();
}

void GeneticServer::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void GeneticServer::bindingProcess(int *sockfd, int *portno, struct sockaddr_in *serv_addr)
{

    *portno = baseSocketNumber;
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(*portno);
    serv_addr->sin_addr.s_addr = INADDR_ANY;
    cout << "Binding to port " << *portno << "..." << endl;
    if (bind(*sockfd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0)
    {
        cout << "Error on Binding: Address already in use" << endl;
        baseSocketNumber += 1;
        bindingProcess(sockfd, portno, serv_addr);
    }
}

void GeneticServer::serverSetup()
{
    std::cout.precision(16);
    int portno;
    int option = 1;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    cout << "Opening Socket..." << endl;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    bindingProcess(&sockfd, &portno, &serv_addr);

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    cout << "Waiting for c! client..." << endl;
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }

    cout << "Connected to GeneticPuzzle client" << endl;
}
