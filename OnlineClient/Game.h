#pragma once
#include <iostream>
#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    sf::TcpSocket socket;
};