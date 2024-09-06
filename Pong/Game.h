#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

enum CommandName
{
	Clear,
	Draw,
	Display,
	Close,
	MoveL,
	MoveR,
	Launch,
	Tick
};

enum PlayState
{
	Waiting,
	Playing
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
	void move(sf::Vector2f delta);
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
	void move(sf::Vector2f delta);
	void setDir(sf::Vector2f dr);
	sf::Vector2f getDir();
	void setDeg(int dg);
private:
	sf::CircleShape body;
	sf::Vector2f dir;
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
	void ballUpdate();
	void boardUpdate();
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
	PlayState playState;
	sf::RectangleShape angleMeter;
	sf::CircleShape angleMeter2;
	float boardSpeed;
	float ballSpeed;
};

