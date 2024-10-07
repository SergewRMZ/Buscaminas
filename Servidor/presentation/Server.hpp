#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <winsock2.h>
#include "./Game/GameController.hpp"

class Server {
  public: 
    WSADATA WSAData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;

    Server(int port);
    ~Server();

    void cleanUpSocket();
    void showSocket();

  private:
    GameController gameController;
    void processMessage (char *buffer);
    void handleClient(SOCKET clientSocket);
};

#endif