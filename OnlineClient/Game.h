#pragma once
#include <iostream>
#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    sf::TcpSocket socket;
};