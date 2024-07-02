//
// Created by mahdi on 6/30/24.
//

#include "connection.h"

#include <iostream>
#include <thread>
#include <array>


connection::connection(int const port) : _port(port)
{
}

connection::~connection()
{
    close(_sock);
}

void connection::start()
{
    createSocket();
    bindSocket();
}

void connection::createSocket()
{
    if (auto const res = socket(AF_INET, SOCK_DGRAM, 0); res > 0)
        this->_sock = res;
    else
        throw std::runtime_error("Can not create socket, Sorry!");
}

void connection::bindSocket()
{
    sockaddr_in addr{};
    addr.sin_port = htons(this->_port);
    addr.sin_family = AF_INET;
    if (auto const res = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr); res != 1)
        throw std::runtime_error("Bad Ip ?");

    if (auto const b = bind(this->_sock, reinterpret_cast<sockaddr const*>(&addr), sizeof(addr)); b != 0)
        throw std::runtime_error("Not able to bind to port: " + std::to_string(this->_port));
}

int connection::sendMessage(int const port, std::string const& message) noexcept
{
    sockaddr_in addr{};
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    if (auto const res = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr); res != 1) return -1;

    return sendto(_sock, message.c_str(), message.size(), 0,
                  reinterpret_cast<sockaddr const*>(&addr), sizeof(addr));
}

std::string connection::receiveMessage() noexcept
{
    char buffer[1024]{0};
    sockaddr_in addr{};
    socklen_t addr_len = sizeof(addr);
    int recv_size = recvfrom(_sock, buffer, 1024, 0, reinterpret_cast<sockaddr*>(&addr), &addr_len);
    if (recv_size > 0)
        return std::string(buffer);

    return "";
}
