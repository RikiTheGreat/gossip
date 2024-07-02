//
// Created by mahdi on 6/30/24.
//

#include "Node.h"

#include <iostream>
#include <random>

Node::Node(int const id, int const port) : _id(id), _port(port)
{
    _connection = std::make_unique<connection>(_port);
}


void Node::startGossip()
{
    try
    {
        _connection->start();
    }
    catch (std::exception const& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return;
    }
}

void Node::sendGossip(std::string const& message)
{
    try
    {
        for (int i = 0; i < _neighbors.size(); ++i)
        {
            if (const auto neighbor = _neighbors.at(giveMeRandomNum()); _connection->sendMessage(neighbor, message) <=
                0)
                throw std::runtime_error("can not send your message!");

            std::cout << "recived message from  " + _connection->receiveMessage() << std::endl;
        }
    }
    catch (std::exception const& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return;
    }
}


int Node::giveMeRandomNum() const noexcept
{
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> unifrom_dist(0, (_neighbors.size() == 0 ? 0 : _neighbors.size() - 1));
    return unifrom_dist(engine);
}

constexpr void Node::setId(int const id) noexcept
{
    this->_id = id;
}

int Node::getId() const noexcept
{
    return _id;
}

constexpr int Node::getPort() const noexcept
{
    return _port;
}

void Node::addNeighbor(int const neighbor) noexcept
{
    _neighbors.push_back(neighbor);
}
