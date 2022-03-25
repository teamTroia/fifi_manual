    #include "Socket.h"
    
    bool Socket::connect(std::string server){
        this->SERVER = server;
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("socket creation failed");
            return false;
        }
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        servaddr.sin_family    = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(SERVER.c_str()); //INADDR_ANY;
        servaddr.sin_port = htons(PORT);

        struct timeval read_timeout;
        read_timeout.tv_sec = 0;
        read_timeout.tv_usec = 10;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout));
        return true;
    }

    bool Socket::bind_sock(){
        if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
            return false;
        }
        return true;
    }

    char* Socket::receive(){
        int n;
        socklen_t len;
        len = sizeof(cliaddr);
        char* buffer = new char[MAXLINE];
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        return buffer;
    }

    void Socket::send(char* message){
        sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    }