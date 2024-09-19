#include "Server.h"

Server::Server()
{
}

Server::~Server()
{
}

void Server::run()
{
	std::cout << "Server started\n";
	if (listener.listen(25566) == sf::Socket::Done)
	{
		std::cout << "Listener started on port " << listener.getLocalPort() << std::endl;
	}
	else
	{
		std::cout << "Listener error\n";
	}

	while (true)
	{
		Connection connection;
		connection.socket = new sf::TcpSocket;
		if (listener.accept(connection.socket[0]) == sf::Socket::Done)
		{
			std::cout << "New connection with ip: " << connection.socket->getRemoteAddress() << std::endl;
			connection.address = connection.socket->getRemoteAddress();
			connections.push_back(connection);
		}
		int i = 0;
		while (i < connections.size())
		{
			sf::Packet packet;
			sf::Socket::Status status = connections[i].socket->receive(packet);
			if (status == sf::Socket::Disconnected)
			{
				std::cout << "Client disconnected with ip: " << connections[i].address << std::endl;;
				connections.erase(connections.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
	return;
}