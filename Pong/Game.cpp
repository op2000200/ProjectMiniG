#include "Game.h"

Game::Game()
	: window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Pong", sf::Style::Fullscreen)
{
	if (sf::VideoMode::getDesktopMode().width > sf::VideoMode::getDesktopMode().height)
	{
		side = sf::VideoMode::getDesktopMode().height / 1;
	}
	else
	{
		side = sf::VideoMode::getDesktopMode().width / 1;
	}
	timePerTick = sf::seconds(1.f / 60.f);
	commandQueue.clear();
	border = new Border(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2));
	ball = new Ball(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2));
	playerBoard = new Board(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2 + side / 3));
	opponentBoard = new Board(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2 - side / 3));
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock tickTimer;
	initialisation();
	while (window.isOpen())
	{
		tickTimer.restart();
		events();
		commands();
		if (tickTimer.getElapsedTime() < timePerTick)
		{
			sf::sleep(sf::Time(timePerTick - tickTimer.getElapsedTime()));
		}
	}
}

void Game::initialisation()
{
}

void Game::events()
{

	//last commands
	Command command;
	command.name = Clear;
	commandQueue.push_back(command);
	command.name = Draw;
	commandQueue.push_back(command);
	command.name = Display;
	commandQueue.push_back(command);
}

void Game::commands()
{
	for (int i = 0; i < commandQueue.size(); i++)
	{
		switch (commandQueue[i].name)
		{
		case Clear:
		{
			window.clear();
			break;
		}
		case Draw:
		{
			window.draw(border->getBody());
			window.draw(ball->getBody());
			window.draw(playerBoard->getBody());
			window.draw(opponentBoard->getBody());
			break;
		}
		case Display:
		{
			window.display();
			break;
		}
		default:
			break;
		}
	}
	commandQueue.clear();
}

Board::Board()
{
}

Board::Board(int side, sf::Vector2f position)
{
	body.setSize(sf::Vector2f(
		side / 10,
		side / 100
	));
	body.setOrigin(sf::Vector2f(
		body.getSize().x / 2,
		body.getSize().y / 2
	));
	body.setPosition(position);
	body.setFillColor(sf::Color::White);
}

Board::~Board()
{
}

sf::RectangleShape Board::getBody()
{
	return body;
}

Ball::Ball()
{
}

Ball::Ball(int side, sf::Vector2f position)
{
	body.setRadius(side / 100);
	body.setOrigin(sf::Vector2f(
		body.getRadius(),
		body.getRadius()
	));
	body.setPosition(position);
	body.setFillColor(sf::Color::White);
}

Ball::~Ball()
{
}

sf::CircleShape Ball::getBody()
{
	return body;
}

Border::Border()
{
}

Border::Border(int side, sf::Vector2f position)
{
	body.setSize(sf::Vector2f(
		side - side / 20,
		side - side / 20
	));
	body.setOrigin(sf::Vector2f(
		body.getSize().x / 2,
		body.getSize().y / 2
	));
	body.setPosition(position);
	body.setOutlineThickness(side / 100.f);
	body.setOutlineColor(sf::Color::White);
	body.setFillColor(sf::Color::Transparent);
}

Border::~Border()
{
}

sf::RectangleShape Border::getBody()
{
	return body;
}
