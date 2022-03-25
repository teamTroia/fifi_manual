#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

#define PORT     8080
#define MAXLINE 1024

class Socket {
    private:
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;
        std::string SERVER;
        
    public:
        bool connect(std::string poty);
        char* receive();
        bool bind_sock();
        void send(char* message);
};