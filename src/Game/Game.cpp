#include <windows.h>
#include <cctype>
#include <iostream>
#include <format>
#include <string>

#include "Game.hpp"
#include "Board.hpp"
#include "File.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"

Game::Game()
	: currentScore(0)
{
	Renderer::loadFont();
	Renderer::loadTextures();
	bestScore = File::loadScore("Score.save");
	this->run();
	// this->bestScore = save.load();
}
Game::~Game(){}
void Game::run()
{
	Board board = Board();
	while (true)
	{
		Renderer::clear();
		if (Input::getPressed("Escape"))
		{
			std::cout << "Closing Programm" << std::endl;
			break;
		}
		if (Input::getPressed("r"))
		{
			board.initialize();
			checkScore();
			currentScore = 0;
		}
		if (!board.gridIsFull())
		{
			currentScore += board.checkMove();
		}
		Renderer::drawText("Score           Meilleur", "Arial", 20, std::tuple<int, int>(300, 400));
		Renderer::drawText(std::to_string(currentScore) + "                 " + std::to_string(bestScore) + "\n", "Arial", 20, std::tuple<int, int>(300, 400));
		board.render();
		Renderer::draw(board.tiles);
		Renderer::drawText("Press r to reset the game", "Arial", 20, std::tuple<int, int>(300, 400));
		if (board.gridIsFull())
		{
			Renderer::drawText("Game ended", "Arial", 20, std::tuple<int, int>(300, 400));
			checkScore();
		}
        Renderer::display();
		Sleep(16);
	}
}

void Game::checkScore()
{
	if (currentScore <= bestScore){return;}
	File::saveScore(currentScore, "Score.save");
	bestScore = currentScore;
}
