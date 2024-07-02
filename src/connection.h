//
// Created by mahdi on 6/30/24.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class connection {
public:
    connection(int port);
    ~connection();
    void start();

    [[nodiscard]] int sendMessage(int port, std::string const& message) noexcept;
    [[nodiscard]] std::string receiveMessage() noexcept;
private:
    void createSocket() ;
    void bindSocket();
private:
    int _port{};
    int _sock{};
};


#endif //CONNECTION_H
