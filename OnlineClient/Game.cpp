#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
	std::cout << "Client started\n";
    sf::Socket::Status status = socket.connect("192.168.0.49", 25565);
    if (status == sf::Socket::Status::Done)
    {
        std::cout << "Connected to server\n";
    }
    else
    {
        std::cout << "Connetction error\n";
    }
	while (true)
	{
	}
	
	return;
}