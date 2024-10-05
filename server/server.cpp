#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

void handle_client(int client_socket, sockaddr_in remote_address) {
  std::string client_ip = inet_ntoa(remote_address.sin_addr);
  int remote_port = ntohs(remote_address.sin_port);

  std::cout << "Accepted new client @ " << client_ip << ":" << remote_port
            << std::endl;

  int BUFFLEN = 1024;
  char buffer[BUFFLEN];

  while (1) {
    memset(buffer, 0, BUFFLEN);
    // 5 recv
    int bytes_received = recv(client_socket, buffer, BUFFLEN - 1, 0);
    if (bytes_received < 0) {
      perror("Could not receive");
      break;
    }
    if (bytes_received == 0) {
      std::cout << "Client at " << client_ip << ":" << remote_port
                << " has disconnected." << std::endl;
      break;
    }

    std::cout << "Received message from client: " << buffer << std::endl;

    // echo response
    std::string responce = "Echo: " + std::string(buffer);
    int bytes_sent =
        send(client_socket, responce.c_str(), responce.length(), 0);
    if (bytes_sent < 0) {
      perror("Could not send");
      break;
    }
  }

  std::cout << "Shutting down socket for client at " << client_ip << ":"
            << remote_port << std::endl;
  shutdown(client_socket, SHUT_RDWR);
  close(client_socket);
};

int main(int argc, char **argv) {

  if (argc < 2) {

    std::cout << "Usage: " << argv[0] << " <port number>" << std::endl;
    return 0;
  }

  int port = atoi(argv[1]);

  // 1 socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {

    perror("Could not create socket");
    return 1;
  }
  // 2 bind
  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  int bind_value = bind(sock, (struct sockaddr *)&address, sizeof(address));
  if (bind_value < 0) {

    perror("Could not bind");
    return 1;
  }
  // 3 listen
  int listen_value = listen(sock, 10);
  if (listen_value < 0) {

    perror("Could not listen");
    return 1;
  }

  std::vector<std::thread> threads;

  std::cout << "Waiting for new connection..." << std::endl;

  while (1) {
    struct sockaddr_in remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    socklen_t remote_addrlen = sizeof(remote_address);

    int client_socket =
        accept(sock, (struct sockaddr *)&remote_address, &remote_addrlen);
    if (client_socket < 0) {
      perror("Could not accept");
      continue;
    }

    threads.emplace_back(handle_client, client_socket, remote_address);
  }

  for (auto &th : threads) {
    if (th.joinable()) {
      th.join();
    }
  }

  close(sock);

  return 0;
}
