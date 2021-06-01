#include "BPServer.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

BPServer::BPServer()
{
    serverSetup();
}

void BPServer::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void BPServer::bindingProcess(int *Sockfd, int *portno, struct sockaddr_in *serv_addr)
{

    *portno = baseSocketNumber;
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(*portno);
    serv_addr->sin_addr.s_addr = INADDR_ANY;
    cout << "Binding to port " << *portno << "..." << endl;
    if (bind(*Sockfd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0)
    {
        cout << "Error on Binding: Address already in use" << endl;
        baseSocketNumber += 1;
        bindingProcess(Sockfd, portno, serv_addr);
    }
}

void BPServer::serverSetup()
{
    std::cout.precision(16);
    int portno;
    int option = 1;
    socklen_t clilen;
    struct sockaddr_in serv_addr
    {
    }, cli_addr{};

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

    cout << "Waiting for BP Game client..." << endl;
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }

    cout << "Connected to BP Game client" << endl;
}

void BPServer::readBuffer()
{
    memset(buffer, 0, 2048);
    char endResult[2048]{};

    cout << "waiting for message..." << endl;
    int n = read(newsockfd, buffer, 2048);
    if (n < 0)
        error("ERROR reading from socket");
    cout << "Message received: '" << buffer << "'" << endl;
    /*   memcpy(endResult, buffer, n);

    int c = n;
    while (buffer[n - 1] != '}')
    {
        int n = read(newsockfd, buffer, 2048);
        if (n < 0)
            error("ERROR reading from socket");
        cout << "Message received: '" << buffer << "'" << endl;
        memcpy(endResult + c, buffer, n - 1);
        memset(buffer, 0, 2048);
        c += n;
    }*/

    cout << "Bytes read: " << n << endl;
}

json BPServer::getBuffer()
{
    json jsonBuffer = json::parse(buffer);
    return jsonBuffer;
}

void BPServer::sendBuffer(json jsonMsg)
{
    string stringMsg = jsonMsg.dump();
    memset(buffer, 0, 2048);
    strncpy(buffer, stringMsg.c_str(), 2048);
    int n = write(newsockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
}

void BPServer::endServer()
{
    close(newsockfd);
    close(sockfd);
}

List<List<int>> BPServer::fixMatrix(List<List<int>> badMatrix)
{
    List<List<int>> goodMatrix;
    for (int i = 0; i < 7; i++)
    {
        List<int> newRow;
        for (int j = 0; j < 11; j++)
        {
            newRow.push_back(badMatrix[j][i]);
        }
        goodMatrix.push_back(newRow);
        goodMatrix[i] = newRow; // must use '=' to create a deep copy
    }
    cout << "Bad Matrix: " << badMatrix << "\nGood Matrix: " << goodMatrix << endl;
    return goodMatrix;
}