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
void Renderer::draw(std::string imageName){}
void Renderer::draw(std::string imageName,Vector2 position,Vector2 size){}
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

void Renderer::drawText(std::string text, std::string fontName, int fontSize, Vector2 pos)
{
	std::cout << text << std::endl;

}

Vector2 Renderer::getResolution(){return Vector2();}

#endif
#ifdef USE_SDL
std::map<std::string,SDL_Texture*> Renderer::images;
std::map<std::string,TTF_Font*> Renderer::fonts;
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
void Renderer::loadTexture(std::string path){
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
	auto font = TTF_OpenFont(path.c_str(), 20);
	if(!font){
		std::cerr << "[Renderer::loadFont] Couldn't load font '" << path << "'." << std::endl;
		return;
	}
	Renderer::fonts[name] = font;
}
void Renderer::draw(std::string imageName){
	Renderer::draw(imageName,Vector2(0,0),Renderer::getResolution());
}
void Renderer::draw(std::string imageName,Vector2 position,Vector2 size){
	SDL_Rect rect = {(int)position.x,(int)position.y,(int)size.x,(int)size.y};
	if(!Renderer::images.contains(imageName)){
		//Draw error/default texture
		return;
	}
	SDL_RenderCopy(Renderer::renderer,Renderer::images[imageName],NULL,&rect);
}
/*void Renderer::draw(int (&board)[4][4]){
	int tileSize = 80;
	int spacing = 5;
	int gridWidth = (4 * tileSize) + (3 * spacing);
	int gridHeight = (4 * tileSize) + (3 * spacing);
	auto resolution = Renderer::getResolution();
	int startX = (resolution.x - gridWidth) / 2;
	int startY = (resolution.y - gridHeight) / 2;

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
			if(Renderer::images.contains(textureKey)){
				SDL_RenderCopy(Renderer::renderer, Renderer::images[textureKey], NULL, &tilesRect);
			}
		}
	}
}*/

void Renderer::drawText(std::string text, std::string fontName, int fontSize, Vector2 pos)
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

	SDL_Rect textRect = {(int)pos.x,(int)pos.y,(int)surface->w,(int)surface->h};

	SDL_RenderCopy(Renderer::renderer, texture, NULL, &textRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

Vector2 Renderer::getResolution()
{
	int width,height;
	SDL_GetRendererOutputSize(Renderer::renderer, &width, &height);
	return Vector2(width, height);
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

void Renderer::draw(std::string imageName){
	Renderer::draw(imageName,Vector2(0,0),Renderer::getResolution());
}
void Renderer::draw(std::string imageName,Vector2 position,Vector2 size){
	if(!Renderer::images.contains(imageName)){
		//Draw error/default texture
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(images[imageName]);
	sprite.setPosition(position.x,position.y);
	window.draw(sprite);
}
// Dessiner un texte
void Renderer::drawText(std::string text, std::string fontName, int fontSize, Vector2 pos) {
	sf::Text sfText;
	sfText.setFont(fonts[fontName]);
	sfText.setString(text);
	sfText.setCharacterSize(fontSize);
	sfText.setPosition(pos.x,pos.y);
	window.draw(sfText);
}

// Obtenir la résolution de la fenêtre
Vector2 Renderer::getResolution() {
	sf::Vector2u size = window.getSize();
	return Vector2(size.x, size.y);
}
#endif
