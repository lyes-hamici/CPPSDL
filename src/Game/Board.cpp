#include <iostream>
#include <random>
#include <cstring>

#include "Board.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"
#include "Game.hpp"

Board::Board(){
	this->tileSize = 80;
	initialize();
}
Board::~Board(){}

void Board::initialize()
{
	reset();
	generateRandomTile();
	generateRandomTile();
}

void Board::reset()
{
	auto spacing = 5;
	auto resolution = Renderer::getResolution();
	auto boardLengths = Vector2(this->tileSize * 4 + spacing * 3);
	auto boardOrigin = (resolution - boardLengths) / 2;
	std::memset(this->cache,0,sizeof(this->cache));
	for(auto x = 0;x < 4;x += 1){
		for(auto y = 0;y < 4;y += 1){
			this->tiles[y][x] = &this->cache[y * 4 + x];
			this->tiles[y][x]->position = boardOrigin + Vector2(x,y) * (this->tileSize + spacing);
		}
	}
}

//--------------Board Logic--------------//
void Board::generateRandomTile()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0,std::size(this->cache) - 1);
	std::uniform_int_distribution<> tilePercent(0, 9);
	int i;
	do{
		i = dist(gen);
	}
	while (cache[i].value != 0);
	cache[i].value = tilePercent(gen) < 9 ? 2 : 4;
}

// Moves
int Board::checkMove()
{
	char direction = 0;
	if (Input::getPressed("Left"))
	{
		direction = 'L';
	}
	else if (Input::getPressed("Right"))
	{
		direction = 'R';
	}
	else if (Input::getPressed("Up"))
	{
		direction = 'U';
	}
	else if (Input::getPressed("Down"))
	{
		direction = 'D';
	}
	if (direction == 0)
	{
		return 0;
	}
	int sum = 0;
	int fordward[4] = {0, 1, 2, 3};
	int backward[4] = {3, 2, 1, 0};
	bool isPositive = (direction == 'L' || direction == 'U');
	bool isHorizontal = (direction == 'L' || direction == 'R');
	int step = isPositive ? 1 : -1;
	bool moved = false;

	for (auto &i : fordward)
	{
		int target = isPositive ? 0 : 3;
		for (auto &j : isPositive ? fordward : backward)
		{
			int x = isHorizontal ? i : j;
			int y = isHorizontal ? j : i;

			if (tiles[x][y]->value != 0)
			{
				if (j != target)
				{
					if (isHorizontal)
					{
						tiles[x][target]->value = tiles[x][y]->value;
					}
					else
					{
						tiles[target][y]->value = tiles[x][y]->value;
					}
					tiles[x][y]->value = 0;
					moved = true;
				}
				target += step;
			}
		}

		for (auto &j : isPositive ? fordward : backward)
		{
			int x = isHorizontal ? i : j;
			int y = isHorizontal ? j : i;

			if (isHorizontal)
			{
				if ((y + step >= 0 && y + step < 4) && tiles[x][y]->value != 0 && tiles[x][y]->value == tiles[x][y + step]->value)
				{
					sum += tiles[x][y]->value * 2;
					tiles[x][y]->value *= 2;
					tiles[x][y + step]->value = 0;
					moved = true;
				}
			}
			else
			{
				if ((x + step >= 0 && x + step < 4) && tiles[x][y]->value != 0 && tiles[x][y]->value == tiles[x + step][y]->value)
				{
					sum += tiles[x][y]->value * 2;
					tiles[x][y]->value *= 2;
					tiles[x + step][y]->value = 0;
					moved = true;
				}
			}
		}

		target = isPositive ? 0 : 3;
		for (auto &j : isPositive ? fordward : backward)
		{
			int x = isHorizontal ? i : j;
			int y = isHorizontal ? j : i;

			if (tiles[x][y]->value != 0)
			{
				if (j != target)
				{
					if (isHorizontal)
					{
						tiles[x][target]->value = tiles[x][y]->value;
					}
					else
					{
						tiles[target][y]->value = tiles[x][y]->value;
					}
					tiles[x][y]->value = 0;
					moved = true;
				}
				target += step;
			}
		}
	}
	if (moved){generateRandomTile();}
	return sum;
}

bool Board::checkAnimations(){
	auto spacing = 5;
	auto resolution = Renderer::getResolution();
	auto boardLengths = Vector2(this->tileSize * 4 + spacing * 3);
	auto boardOrigin = (resolution - boardLengths) / 2;
	auto done = true;
	for(auto x = 0;x < 4;x += 1){
		for(auto y = 0;y < 4;y += 1){
			auto destination = boardOrigin + Vector2(y,x) * (this->tileSize + spacing);
			auto& position = this->tiles[y][x]->position;
			if(position == destination){continue;}
			position = position.MoveTowards(destination,10000 * Game::deltaTime);
			done = false;
		}
	}
	return done;
}
void Board::render(){
	auto spacing = 5;
	auto resolution = Renderer::getResolution();
	auto boardLengths = Vector2(this->tileSize * 4 + spacing * 3);
	auto origin = (resolution - boardLengths) / 2;
	Renderer::draw("Grid_background",origin - 15,boardLengths + 30);
	for(auto tile : this->cache){
		Renderer::draw(std::to_string(tile.value),tile.position,this->tileSize);
	}
}

bool Board::gridIsFull(){
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			auto isEmpty = tiles[i][j]->value == 0;
			auto canMergeHorizontal = j < 3 && tiles[i][j]->value == tiles[i][j + 1]->value;
			auto canMergeVertical = i < 3 && tiles[i][j]->value == tiles[i + 1][j]->value;
			if(isEmpty || canMergeHorizontal || canMergeVertical){
				return false;
			}
		}
	}
	return true;
}

// int main()
// {
//     Input::initialize();
//     Board board = Board();
//     while (true)
//     {
//         Sleep(100);
//         board.checkMove();
//         board.printBoard(board.board);
//         // system("cls");
//         if (Input::getPressed("Escape"))
//         {
//             std::cout << "Closing Programm" << std::endl;
//             return 0;
//         }

//         if (Input::getPressed("r"))
//         {
//             board.initializeBoard();
//         }
//     }
//     return 0;
// }