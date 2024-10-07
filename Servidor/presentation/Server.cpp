#include <iostream>
#include <winsock2.h>
#include "Server.hpp"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

Server:: Server (int port) {
  // Inicializar WinSock
  if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
      cout << "Error al inicializar Winsock." << endl;
      exit(EXIT_FAILURE);
  }

  // AF_INET: IPv4, SOCK_STREAM, 0: TCP
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  if (serverSocket == INVALID_SOCKET) {
    cout << "Error al crear el socket." << endl;
    WSACleanup();
    exit(EXIT_FAILURE);
  }

  serverAddr.sin_family = AF_INET; // IPv4
  // serverAddr.sin_addr.s_addr = INADDR_ANY; // Aceptar conexiones desde cualquier direcciónIP
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddr.sin_port = htons(port); // Puerto

  // bind (descriptor socket, apuntador que asocia la IP y el puerto, tamaño de la estructura)
  if (bind(serverSocket, (SOCKADDR *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    cout << "Error al enlazar el socket." << endl;
    cleanUpSocket();
  }

  // listen(descriptor del servidor, backlog)
  if (listen(serverSocket, 5) == SOCKET_ERROR) {
    cout << "Error al escuchar en el socket." << endl;
    cleanUpSocket();
  }

  cout << "Esperando conexiones en el puerto " << port << "..." << endl;
  this->showSocket();

  while(true) {
    int clientSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (SOCKADDR *) &clientAddr, &clientSize);

    if (clientSocket == INVALID_SOCKET) {
        cout << "Error al aceptar la conexión." << endl;
        // cleanUpSocket();
        continue;
    }

    cout << "Cliente conectado." << endl;
    thread clientThread(&Server::handleClient, this, clientSocket);
    clientThread.detach(); 
  }
}

void Server::handleClient(SOCKET clientSocket) {
  char buffer[1024];

  while (true) {
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
      buffer[bytesReceived] = '\0';
      cout << "Mensaje recibido del cliente: " << buffer << endl;
      this->processMessage(buffer);
    }

    else {
      cout << "Cliente desconectado." << endl;
      closesocket(clientSocket);
      break;  
    }
  }
}

// Destructor
Server::~Server () {
  closesocket(clientSocket);
  closesocket(serverSocket);
  WSACleanup();
}

void Server::cleanUpSocket () {
  closesocket(serverSocket);
  // closesocket(clientSocket);
  WSACleanup();
  exit(EXIT_FAILURE);
}

void Server::showSocket () {
  SOCKADDR_IN localAddr;
  int addrLen = sizeof(localAddr);

  if (getsockname(serverSocket, (SOCKADDR*)&localAddr, &addrLen) == SOCKET_ERROR) {
    cout << "Error al obtener la dirección IP asignada." << endl;
    return;
  }

  // Convertir la dirección IP a una cadena legible
  cout << "IP asignada: " << inet_ntoa(localAddr.sin_addr) << endl;
  cout << "Puerto asignado: " << ntohs(localAddr.sin_port) << endl;
}


/* .c_str() función que devuelve un puntero a un arreglo de caracteres (const char *)
que representa la cadena */
void Server::processMessage (char *buffer) {
  try {
    json j = json::parse(buffer);
    string action = j["action"];
    string response;

    if (action == "start") {
      string difficulty = j["difficulty"];
      response = this->gameController.initGame(difficulty);
    }

    else if (action == "reveal") {
      json cell = j["cell"];
      int row = cell["row"];
      int col = cell["col"];
      response = this->gameController.revealCell(row, col);
    }

    else if (action == "getranking") {
      response = this->gameController.getRanking();
    }

    // Envíar respuesta al cliente
    int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent == SOCKET_ERROR)
      cout << "Error al enviar los datos" << endl;
    else 
      cout << "Enviados " << bytesSent << " bytes al cliente." << endl;
  }
  
  catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}
