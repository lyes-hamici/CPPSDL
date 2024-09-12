#include <windows.h>
#include <cctype>
#include <iostream>
#include <format>
#include <filesystem>
#include "Game.hpp"
#include "Board.hpp"
#include "File.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"

Game::Game()
{
	this->currentScore = 0;
	this->texturesPath = "Images/";
	this->fontsPath = "Fonts/";
	for(auto& file : std::filesystem::directory_iterator(this->texturesPath)){
		Renderer::loadTexture(file.path().string());
	}
	for(auto& file : std::filesystem::directory_iterator(this->fontsPath)){
		Renderer::loadFont(file.path().string());
	}
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
		Renderer::drawText("Score           Meilleur", "arial", 20, std::tuple<int, int>(300, 400));
		Renderer::drawText(std::to_string(currentScore) + "                 " + std::to_string(bestScore) + "\n", "arial", 20, std::tuple<int, int>(300, 400));
		board.render();
		Renderer::draw(board.tiles);
		Renderer::drawText("Press r to reset the game", "arial", 20, std::tuple<int, int>(300, 400));
		if (board.gridIsFull())
		{
			Renderer::drawText("Game ended", "arial", 20, std::tuple<int, int>(300, 400));
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
