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
	ball = new Ball(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2 + side / 3 - side / 25));
	playerBoard = new Board(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2 + side / 3));
	opponentBoard = new Board(side, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2 - side / 3));
	playState = Waiting;
	angleMeter.setSize(sf::Vector2f(
		side / 10,
		side / 100
	));
	angleMeter.setOrigin(sf::Vector2f(
		0,
		angleMeter.getSize().y / 2
	));
	angleMeter.setPosition(sf::Vector2f(0,0));
	angleMeter.setFillColor(sf::Color::White);
	angleMeter.setRotation(-90);
	angleMeter2.setRadius(1);
	angleMeter2.setOrigin(sf::Vector2f(
		angleMeter2.getRadius(),
		angleMeter2.getRadius()
	));
	angleMeter2.setPosition(sf::Vector2f(0,0));
	angleMeter2.setFillColor(sf::Color::White);
	angleMeter2.setPointCount(360);
	ballSpeed = side / 4;
	boardSpeed = side / 2;
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
	srand(time(0));
}

void Game::events()
{
	Command command;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		command.name = Close;
		commandQueue.push_back(command);
	}
	if (playState == Waiting)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			command.name = Launch;
			commandQueue.push_back(command);
		}
	}
	if (playState == Playing)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			command.name = MoveL;
			commandQueue.push_back(command);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			command.name = MoveR;
			commandQueue.push_back(command);
		}
	}

	//last commands

	command.name = Tick;
	commandQueue.push_back(command);
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
			window.draw(angleMeter);
			break;
		}
		case Display:
		{
			window.display();
			break;
		}
		case Close:
		{
			window.close();
			break;
		}
		case Launch:
		{
			playState = Playing;
			int deg = rand() % 60 - 30;
			//int deg = 60;
			ball->setDeg(deg);
			break;
		}
		case Tick:
		{
			//move ball
			if (playState == Playing)
			{
				ballUpdate();
				boardUpdate();
			}
			break;
		}
		case MoveL:
		{
			sf::Vector2f delta;
			for (int i = 0; i < 10; i++)
			{
				delta.x = (-0.1 * i) * timePerTick.asSeconds() * boardSpeed;
				if (playerBoard->getBody().getPosition().x - playerBoard->getBody().getSize().x / 2 - delta.x < border->getBody().getPosition().x - border->getBody().getSize().x / 2)
				{
					break;
				}
			}
			delta.y = 0;
			playerBoard->move(delta);
			break;
		}
		case MoveR:
		{
			sf::Vector2f delta;
			for (int i = 0; i < 10; i++)
			{
				delta.x = (0.1 * i) * timePerTick.asSeconds() * boardSpeed;
				if (playerBoard->getBody().getPosition().x + playerBoard->getBody().getSize().x / 2 + delta.x > border->getBody().getPosition().x + border->getBody().getSize().x / 2)
				{
					break;
				}
			}
			delta.y = 0;
			playerBoard->move(delta);
			break;
		}
		default:
			break;
		}
	}
	commandQueue.clear();
}

void Game::ballUpdate()
{
	sf::Vector2f delta;

	delta.x = (angleMeter2.getPoint(ball->getBody().getRotation()).x - 1) * timePerTick.asSeconds() * ballSpeed;
	delta.y = (angleMeter2.getPoint(ball->getBody().getRotation()).y - 1) * timePerTick.asSeconds() * ballSpeed;
	if (ball->getBody().getPosition().y - ball->getBody().getRadius() + delta.y < opponentBoard->getBody().getPosition().y + opponentBoard->getBody().getSize().y / 2)
	{
		if (ball->getBody().getPosition().x + ball->getBody().getRadius() > opponentBoard->getBody().getPosition().x - opponentBoard->getBody().getSize().x / 2 and ball->getBody().getPosition().x - ball->getBody().getRadius() < opponentBoard->getBody().getPosition().x + opponentBoard->getBody().getSize().x / 2)
		{
			if (ball->getBody().getPosition().x == opponentBoard->getBody().getPosition().x)
			{
				ball->setDeg(180 - ball->getBody().getRotation());
			}
			if (ball->getBody().getPosition().x < opponentBoard->getBody().getPosition().x)
			{
				if (ball->getBody().getPosition().x < opponentBoard->getBody().getPosition().x - opponentBoard->getBody().getSize().x / 4)
				{
					ball->setDeg(175 - ball->getBody().getRotation());
				}
				else
				{
					ball->setDeg(178 - ball->getBody().getRotation());
				}
			}
			if (ball->getBody().getPosition().x > opponentBoard->getBody().getPosition().x)
			{
				if (ball->getBody().getPosition().x > opponentBoard->getBody().getPosition().x + opponentBoard->getBody().getSize().x / 4)
				{
					ball->setDeg(185 - ball->getBody().getRotation());
				}
				else
				{
					ball->setDeg(182 - ball->getBody().getRotation());
				}
			}
		}
	}
	if (ball->getBody().getPosition().y + ball->getBody().getRadius() + delta.y > playerBoard->getBody().getPosition().y - playerBoard->getBody().getSize().y / 2)
	{
		if (ball->getBody().getPosition().x + ball->getBody().getRadius() > playerBoard->getBody().getPosition().x - playerBoard->getBody().getSize().x / 2 and ball->getBody().getPosition().x - ball->getBody().getRadius() < playerBoard->getBody().getPosition().x + playerBoard->getBody().getSize().x / 2)
		{
			if (ball->getBody().getPosition().x == playerBoard->getBody().getPosition().x)
			{
				ball->setDeg(180 - ball->getBody().getRotation());
			}
			if (ball->getBody().getPosition().x < playerBoard->getBody().getPosition().x)
			{
				if (ball->getBody().getPosition().x < playerBoard->getBody().getPosition().x - playerBoard->getBody().getSize().x / 4)
				{
					ball->setDeg(160 - ball->getBody().getRotation());
				}
				else
				{
					ball->setDeg(170 - ball->getBody().getRotation());
				}
			}
			if (ball->getBody().getPosition().x > playerBoard->getBody().getPosition().x)
			{
				if (ball->getBody().getPosition().x > playerBoard->getBody().getPosition().x + playerBoard->getBody().getSize().x / 4)
				{
					ball->setDeg(200 - ball->getBody().getRotation());
				}
				else
				{
					ball->setDeg(190 - ball->getBody().getRotation());
				}
			}
		}
	}
	if (ball->getBody().getPosition().x - ball->getBody().getRadius() + delta.x < border->getBody().getPosition().x - border->getBody().getSize().x / 2)
	{
		ball->setDeg(-ball->getBody().getRotation());
	}
	if (ball->getBody().getPosition().x + ball->getBody().getRadius() + delta.x > border->getBody().getPosition().x + border->getBody().getSize().x / 2)
	{
		ball->setDeg(-ball->getBody().getRotation());
	}
	ball->move(delta);
	ballSpeed += side / 2000;
	if (ball->getBody().getPosition().y - ball->getBody().getRadius() < opponentBoard->getBody().getPosition().y + opponentBoard->getBody().getSize().y / 2)
	{
		//win
	}
	if (ball->getBody().getPosition().y + ball->getBody().getRadius() > playerBoard->getBody().getPosition().y - playerBoard->getBody().getSize().y / 2)
	{
		//lose
	}
}

void Game::boardUpdate()
{
	if (ball->getBody().getPosition().x < opponentBoard->getBody().getPosition().x)
	{
		//go left
		sf::Vector2f delta;
		for (int i = 0; i < 10; i++)
		{
			delta.x = (-0.1 * i) * timePerTick.asSeconds() * boardSpeed;
			if (opponentBoard->getBody().getPosition().x - opponentBoard->getBody().getSize().x / 2 - delta.x < border->getBody().getPosition().x - border->getBody().getSize().x / 2)
			{
				break;
			}
		}
		delta.y = 0;
		opponentBoard->move(delta);
	}
	if (ball->getBody().getPosition().x > opponentBoard->getBody().getPosition().x)
	{
		//go right
		sf::Vector2f delta;
		for (int i = 0; i < 10; i++)
		{
			delta.x = (0.1 * i) * timePerTick.asSeconds() * boardSpeed;
			if (opponentBoard->getBody().getPosition().x + opponentBoard->getBody().getSize().x / 2 + delta.x > border->getBody().getPosition().x + border->getBody().getSize().x / 2)
			{
				break;
			}
		}
		delta.y = 0;
		opponentBoard->move(delta);
	}
}

Board::Board()
{
}

Board::Board(int side, sf::Vector2f position)
{
	body.setSize(sf::Vector2f(
		side / 10,
		side / 75
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

void Board::move(sf::Vector2f delta)
{
	body.move(delta);
}

Ball::Ball()
{
}

Ball::Ball(int side, sf::Vector2f position)
{
	body.setRadius(side / 50);
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

void Ball::move(sf::Vector2f delta)
{
	body.move(delta);
}

void Ball::setDir(sf::Vector2f dr)
{
	dir = dir;
}

sf::Vector2f Ball::getDir()
{
	return dir;
}

void Ball::setDeg(int dg)
{
	body.setRotation(dg);
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
