#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

enum CommandName
{
	Clear,
	Draw,
	Display
};

struct Command
{
	CommandName name;
};

class Board
{
public:
	Board();
	Board(int side, sf::Vector2f position);
	~Board();

	sf::RectangleShape getBody();
private:
	sf::RectangleShape body;
};

class Ball
{
public:
	Ball();
	Ball(int side, sf::Vector2f position);
	~Ball();

	sf::CircleShape getBody();
private:
	sf::CircleShape body;
};

class Border
{
public:
	Border();
	Border(int side, sf::Vector2f position);
	~Border();

	sf::RectangleShape getBody();

private:
	sf::RectangleShape body;
};

class Game
{
public:
	Game();
	~Game();

	void run();
	void initialisation();
	void events();
	void commands();
private:
	int side;
	sf::RenderWindow window;
	sf::Time timePerTick;
	sf::Font mainFont;
	std::vector<Command> commandQueue;
	Board* playerBoard;
	Board* opponentBoard;
	Ball* ball;
	Border* border;
};

