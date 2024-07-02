//
// Created by mahdi on 6/30/24.
//

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

#include "connection.h"

class Node
{
public:
    Node(int, int);
    constexpr void setId(int id) noexcept;
    [[nodiscard]] int getId() const noexcept;
    [[nodiscard]] constexpr int getPort() const noexcept;
    void startGossip();
    void addNeighbor(int neighbor) noexcept;
    void sendGossip(std::string const& message);

private:
    [[nodiscard]] int giveMeRandomNum() const noexcept;

private:
    int _id{};
    int _port{};
    std::vector<int> _neighbors;
    std::unique_ptr<connection> _connection;
};


#endif //NODE_H
