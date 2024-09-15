#include <windows.h>
#include <cctype>
#include <iostream>
#include <format>
#include <filesystem>
#include <chrono>
#include "Game.hpp"
#include "Board.hpp"
#include "File.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"
float Game::deltaTime;
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
void Game::run(){
	Board board = Board();
	while(true){
		auto startTime = std::chrono::high_resolution_clock::now();
		int spacing = 5;
		auto resolution = Renderer::getResolution();
		auto boardLengths = Vector2(board.tileSize * 4 + spacing * 3);
		auto boardOrigin = (resolution - boardLengths) / 2;
		auto scoreOrigin = Vector2(boardOrigin.x - 40,20);
		auto infoOrigin = Vector2(boardOrigin.x - 40,boardLengths.y + boardOrigin.y + 60);
		Renderer::clear();
		if(Input::getPressed("Escape")){
			std::cout << "Closing Programm" << std::endl;
			break;
		}
		if(Input::getPressed("r")){
			board.initialize();
			checkScore();
			currentScore = 0;
		}
		if(!board.gridIsFull()){
			currentScore += board.checkMove();
		}
		//board.checkAnimations();
		Renderer::draw("Background");
		Renderer::draw("Score",scoreOrigin,Vector2(boardLengths.x + 80,100));
		Renderer::drawText("Score                                     Meilleur","arial",20,scoreOrigin + Vector2(40,20));
		Renderer::drawText(std::format("{}                                         {}",currentScore,bestScore),"arial",20,scoreOrigin + Vector2(60,40));
		board.render();
		Renderer::draw("Text",infoOrigin,Vector2(boardLengths.x + 80,100));
		Renderer::drawText("Press r to reset the game","arial",20,infoOrigin + Vector2(90,35));
		if(board.gridIsFull()){
			Renderer::drawText("Game ended", "arial", 20, infoOrigin + Vector2(90,60));
			checkScore();
		}
        Renderer::display();
		auto endTime = std::chrono::high_resolution_clock::now();
		Game::deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(endTime - startTime).count();
		Sleep(16);
	}
}

void Game::checkScore()
{
	if (currentScore <= bestScore){return;}
	File::saveScore(currentScore, "Score.save");
	bestScore = currentScore;
}
