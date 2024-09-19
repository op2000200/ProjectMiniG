#pragma once
#include <iostream>
#include "SFML/Network.hpp"
#include <vector>

struct Connection
{
	sf::TcpSocket* socket;
	sf::IpAddress address;
};


class Server
{
public:
	Server();
	~Server();
	void run();

private:
	std::vector<Connection> connections;
	sf::TcpListener listener;
};
