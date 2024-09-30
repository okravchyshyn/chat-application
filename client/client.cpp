#include <arpa/inet.h>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc < 3) {

    std::cout << "Usage: " << argv[0] << " <server IP> <port number>"
              << std::endl;
    return 0;
  }

  const char *server_ip = argv[1];
  int port = atoi(argv[2]);

  // 1 socket

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Could not create socket");
    return 1;
  }

  // 2 bind
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);

  // 3 inet_pton
  if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
    perror("Invalid address");
    close(sock);
    return 1;
  }
  // 4 connect
  if (connect(sock, (struct sockaddr *)&server_address,
              sizeof(server_address))) {
    perror("Could not connect");
    close(sock);
    return 1;
  }

  std::cout << "Connected to server at " << server_ip << ":" << port
            << std::endl;

  // 5 enter a message

  int BUFFLEN = 1024;
  char buffer[BUFFLEN];

  while (1) {
    std::cout << "Enter message to send (or type 'exit' to quit): ";
    std::string message;
    std::getline(std::cin, message);

    if (message == "exit")
      break;

    // 6 send
    int bytes_sent = send(sock, message.c_str(), message.length(), 0);
    if (bytes_sent < 0) {
      perror("Could not send");
      close(sock);
      return 1;
    }
  }
  close(sock);
  return 0;
}
