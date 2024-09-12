#include "Renderer.hpp"

#ifdef USE_WINDOWSCONSOLE
void Renderer::initialize(){}

void Renderer::destroy(){}

void Renderer::clear(){
	system("cls");
}

void Renderer::display(){}

void Renderer::loadTexture(std::string path){}

void Renderer::loadFont(std::string path){}

void Renderer::draw(){}
void Renderer::draw(int (&board)[4][4]){}

void Renderer::drawRow(void *row, int size)
{
	int *intRow = (int *)row;

	int width = 5;

	for (int j = 0; j < size; j++)
	{
		std::cout << std::setw(width) << intRow[j] << " ";
	}

	std::cout << "\n" << std::endl;
}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos)
{
	std::cout << text << std::endl;

}

std::tuple<int, int> Renderer::getResolution()
{
	return std::tuple<int,int>();
}

#endif
#ifdef USE_SDL
std::map<std::string, SDL_Texture*> Renderer::images;
std::map<std::string, TTF_Font*> Renderer::fonts;
std::map<std::string,std::string> Renderer::imageFormats;
std::map<std::string,std::string> Renderer::fontFormats;
SDL_Window* Renderer::window;
SDL_Renderer* Renderer::renderer;

void Renderer::initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_AVIF);
	Renderer::window = SDL_CreateWindow("Ma Fenêtre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 700, SDL_WINDOW_SHOWN);
	Renderer::imageFormats[".png"] = "PNG";
	Renderer::imageFormats[".jpg"] = "JPEG";
	Renderer::imageFormats[".avif"] = "AV1 Image File Format";
	Renderer::fontFormats[".ttf"] = "TrueType Font";
	if (window == nullptr)
	{
		std::cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	Renderer::renderer = SDL_CreateRenderer(Renderer::window, -1, SDL_RENDERER_ACCELERATED);
	if (Renderer::renderer == nullptr)
	{
		std::cerr << "Erreur lors de la création du renderer: " << std::endl;
		SDL_DestroyWindow(Renderer::window);
		SDL_Quit();
	}
}

void Renderer::destroy(){}

void Renderer::clear()
{
	SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer::renderer);
}

void Renderer::display()
{
	SDL_RenderPresent(Renderer::renderer);
}
void Renderer::loadTexture(std::string path)
{
	auto extensionIndex = path.find_last_of(".");
	if(extensionIndex == std::string::npos){
		std::cerr << "[Renderer::loadTexture] No extension for image '" << path << "'." << std::endl;
		return;
	}
	auto extension = path.substr(extensionIndex);
	if(!Renderer::imageFormats.contains(extension)){
		std::cerr << "[Renderer::loadTexture] Extension '" << extension << "' not supported." << std::endl;
		return;
	}
	auto lastScope = std::max<int>(path.find_last_of('\\'),path.find_last_of("/"));
	auto name = path.substr(lastScope + 1,path.find_last_of('.') - lastScope - 1);
	auto surface = IMG_Load(path.c_str());
	if(!surface){
		std::cerr << "[Renderer::loadTexture] Couldn't load image '" << path << "'." << std::endl;
	}
	Renderer::images[name] = SDL_CreateTextureFromSurface(Renderer::renderer,surface);
	SDL_FreeSurface(surface);
}

void Renderer::loadFont(std::string path)
{
	auto extensionIndex = path.find_last_of(".");
	if(extensionIndex == std::string::npos){
		std::cerr << "[Renderer::loadFont] No extension for font '" << path << "'." << std::endl;
		return;
	}
	auto extension = path.substr(extensionIndex);
	if(!Renderer::fontFormats.contains(extension)){
		std::cerr << "[Renderer::loadFont] Extension '" << extension << "' not supported." << std::endl;
		return;
	}
	auto lastScope = std::max<int>(path.find_last_of('\\'),path.find_last_of("/"));
	auto name = path.substr(lastScope + 1,path.find_last_of('.') - lastScope - 1);
	auto font = TTF_OpenFont(path.c_str(), 20);
	if(!font){
		std::cerr << "[Renderer::loadFont] Couldn't load font '" << path << "'." << std::endl;
		return;
	}
	Renderer::fonts[name] = font; 
}

void Renderer::draw()
{                        // Clear the screen
	int xPosition = 0;     // Initial x position
	int yPosition = 50;    // Fixed y position (line)
	int imageWidth = 50;  // Width of each image
	int imageHeight = 50; // Height of each image
	int spacing = 10;      // Space between images

	for (int i = 2; i < 65537; i *= 2)
	{
		SDL_Rect dstRect = {xPosition, yPosition, imageWidth, imageHeight}; // Set position and size
		SDL_RenderCopy(Renderer::renderer, Renderer::images[std::to_string(i)], NULL, &dstRect);

		xPosition += imageWidth + spacing; // Move x position for next image
	}

	SDL_RenderPresent(Renderer::renderer); // Display rendered content
}
void Renderer::draw(int (&board)[4][4])
{
	SDL_RenderCopy(Renderer::renderer, Renderer::images["Background"], NULL, NULL);
	
	int tileSize = 80;                              
	int spacing = 5;                                
	int gridWidth = (4 * tileSize) + (3 * spacing);  
	int gridHeight = (4 * tileSize) + (3 * spacing); 

	int startX = (600 - gridWidth) / 2;
	int startY = (700 - gridHeight) / 2;

	SDL_Rect gridBackgroundRect = {startX - 15, startY - 15, gridWidth + 30, gridHeight + 30};
	SDL_SetTextureAlphaMod(Renderer::images["Grid_background"], 200);
	SDL_RenderCopy(Renderer::renderer, Renderer::images["Grid_background"], NULL, &gridBackgroundRect);
	
	SDL_Rect scoreRect = {startX, 20, gridWidth + 80, 100};
	SDL_Rect textRect = {startX - 40, gridHeight + startY + 60, gridWidth + 80, 100};
	SDL_RenderCopy(Renderer::renderer, Renderer::images["Text"], NULL, &textRect);
	SDL_RenderCopy(Renderer::renderer, Renderer::images["Score"], NULL, &scoreRect);

	for (int row = 0; row < 4; ++row){
		for (int col = 0; col < 4; ++col){
			int value = board[row][col]; 
			SDL_Rect tilesRect = {
				startX + col * (tileSize + spacing),
				startY + row * (tileSize + spacing), 
				tileSize,                            
				tileSize                             
			};
			std::string textureKey = std::to_string(value);
			if (Renderer::images.find(textureKey) != Renderer::images.end()){
				SDL_RenderCopy(Renderer::renderer, Renderer::images[textureKey], NULL, &tilesRect);
			}
		}
	}
}

void Renderer::drawRow(void *row, int size)
{

}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos)
{
	if (!Renderer::fonts.contains(fontName))
	{
		std::cerr << "Font not found: " << fontName << std::endl;
		return;
	}
	SDL_Color color = {0, 0, 0, 255};

	SDL_Surface *surface = TTF_RenderText_Solid(Renderer::fonts[fontName], text.c_str(), color);
	if (surface == NULL)
	{
		std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::renderer, surface);
	if (texture == NULL)
	{
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		return;
	}

	SDL_Rect textRect = {std::get<0>(pos), std::get<1>(pos), surface->w, surface->h};

	SDL_RenderCopy(Renderer::renderer, texture, NULL, &textRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

std::tuple<int, int> Renderer::getResolution()
{
	int width,height;
	SDL_GetRendererOutputSize(Renderer::renderer, &width, &height);
	return std::make_tuple(width, height);
}

#endif

#ifdef USE_SFML

sf::RenderWindow Renderer::window;
std::map<std::string, sf::Texture> Renderer::images;
std::map<std::string, sf::Font> Renderer::fonts;
std::map<std::string,std::string> Renderer::imageFormats;
std::map<std::string,std::string> Renderer::fontFormats;

void Renderer::initialize(){
	window.create(sf::VideoMode(600,700),"SFML 2048");
	Renderer::imageFormats[".png"] = "PNG";
	Renderer::fontFormats[".ttf"] = "TrueType Font";
}

// Détruire la fenêtre (si nécessaire)
void Renderer::destroy() {
	if (window.isOpen()) {
		window.close();
	}
}

// Effacer la fenêtre
void Renderer::clear() {
	window.clear();
}

void Renderer::display()
{
	window.display();
}

// Charger une texture depuis un fichier
void Renderer::loadTexture(std::string path) {
	auto extensionIndex = path.find_last_of(".");
	if(extensionIndex == std::string::npos){
		std::cerr << "[Renderer::loadTexture] No extension for image '" << path << "'." << std::endl;
		return;
	}
	auto extension = path.substr(extensionIndex);
	if(!Renderer::imageFormats.contains(extension)){
		std::cerr << "[Renderer::loadTexture] Extension '" << extension << "' not supported." << std::endl;
		return;
	}
	auto lastScope = std::max<int>(path.find_last_of('\\'),path.find_last_of("/"));
	auto name = path.substr(lastScope + 1,path.find_last_of('.') - lastScope - 1);
	sf::Texture texture;
	if(!texture.loadFromFile(path)){
		std::cerr << "[Renderer::loadTexture] Couldn't load image '" << path << "'." << std::endl;
		return;
	}
	Renderer::images[name] = texture;
}

// Charger une police depuis un fichier
void Renderer::loadFont(std::string path){
	auto extensionIndex = path.find_last_of(".");
	if(extensionIndex == std::string::npos){
		std::cerr << "[Renderer::loadFont] No extension for font '" << path << "'." << std::endl;
		return;
	}
	auto extension = path.substr(extensionIndex);
	if(!Renderer::fontFormats.contains(extension)){
		std::cerr << "[Renderer::loadFont] Extension '" << extension << "' not supported." << std::endl;
		return;
	}
	auto lastScope = std::max<int>(path.find_last_of('\\'),path.find_last_of("/"));
	auto name = path.substr(lastScope + 1,path.find_last_of('.') - lastScope - 1);
	sf::Font font;
	if(!font.loadFromFile(path)){  // Adjust path to Arial font
		std::cerr << "[Renderer::loadFont] Couldn't load font '" << path << "'." << std::endl;
		return;
	}
	Renderer::fonts[name] = font;
}

// Dessiner une texture spécifique
void Renderer::draw() {
}
void Renderer::drawRow(void *row, int size){}

// Dessiner un texte
void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos) {
	sf::Text sfText;
	sfText.setFont(fonts[fontName]);
	sfText.setString(text);
	sfText.setCharacterSize(fontSize);
	sfText.setPosition(std::get<0>(pos), std::get<1>(pos));
	window.draw(sfText);
}

// Dessiner une grille de jeu (board)
// Draw the game board (4x4 grid for the 2048 game)
void Renderer::draw(int (&board)[4][4]) {
	float tileSize = 70.0f;  // Size of each tile
	float spacing = 60.0f;    
	int gridSize = 4;         // Size of the grid (4x4 for 2048 game)

	// Calculate the total width and height of the board (including tiles and spacing)
	float boardWidth = gridSize * tileSize + (gridSize - 1) * spacing;
	float boardHeight = gridSize * tileSize + (gridSize - 1) * spacing;

	// Get the size of the window
	sf::Vector2u windowSize = window.getSize();

	// Calculate the offset to center the board in the window
	float offsetX = (windowSize.x - boardWidth) / 3.0f;
	float offsetY = (windowSize.y - boardHeight) / 4.0f;

	// Loop through the 4x4 board to draw each tile
	for (size_t row = 0; row < gridSize; ++row) {
		for (size_t col = 0; col < gridSize; ++col) {
			int value = board[row][col];

			// Calculate the position considering spacing and centering
			float xPosition = offsetX + col * (tileSize + spacing);
			float yPosition = offsetY + row * (tileSize + spacing);

			// If the tile has a value greater than 0, load the corresponding texture
			if (value > 0) {
				sf::Sprite sprite;
				sprite.setTexture(images[std::to_string(value)]);
				sprite.setPosition(xPosition, yPosition);
				window.draw(sprite);
			} else {
				// If the value is 0, load the "0.png" texture (empty tile)
				sf::Sprite sprite;
				sprite.setTexture(images["0"]);
				sprite.setPosition(xPosition, yPosition);
				window.draw(sprite);
			}
		}
	}  
}




// Obtenir la résolution de la fenêtre
std::tuple<int, int> Renderer::getResolution() {
	sf::Vector2u size = window.getSize();
	return std::tuple<int, int>(size.x, size.y);
}




#endif