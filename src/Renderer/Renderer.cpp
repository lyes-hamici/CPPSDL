#include "Renderer.hpp"

#ifdef USE_WINDOWSCONSOLE
HANDLE Renderer::buffer;
void Renderer::initialize(){
	COORD size = {200,100};
	Renderer::buffer = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
	SetConsoleScreenBufferSize(Renderer::buffer,size);
}

void Renderer::destroy(){}

void Renderer::clear(){
	system("cls");
}

void Renderer::display(){}

void Renderer::loadTexture(std::string path){}

void Renderer::loadFont(std::string path){}
void Renderer::draw(std::string imageName){
	Renderer::draw(imageName,Vector2(0,0),Renderer::getResolution());
}
void Renderer::draw(std::string imageName,Vector2 position,Vector2 size){
	std::string::const_iterator it = imageName.begin();
    while (it != imageName.end() && std::isdigit(*it)) ++it;
    auto isNumber = !imageName.empty() && it == imageName.end();
	if(!isNumber){return;}
	COORD bufferPosition = {(short)position.x,(short)position.y};
	COORD rectSize = {(short)imageName.length(),0};
	CHAR_INFO text[imageName.length()];
	for(auto index = 0;index < imageName.length();index += 1){
		text[index].Char.UnicodeChar = imageName[index];
	}
	WriteConsoleOutput(Renderer::buffer,text,rectSize,bufferPosition,NULL);
}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, Vector2 position)
{
	COORD bufferPosition = {(short)position.x,(short)position.y};
	COORD rectSize = {(short)text.length(),0};
	CHAR_INFO characters[text.length()];
	for(auto index = 0;index < text.length();index += 1){
		characters[index].Char.UnicodeChar = text[index];
	}
	WriteConsoleOutput(Renderer::buffer,characters,rectSize,bufferPosition,NULL);
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

void Renderer::drawText(std::string text, std::string fontName, int fontSize, Vector2 pos)
{
	if (!Renderer::fonts.contains(fontName))
	{
		std::cerr << "Font not found: " << fontName << std::endl;
		return;
	}
	SDL_Color color = {255, 255, 255, 255};

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
sf::Event ev;

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

	if (window.pollEvent(ev)){
		window.display();
	}
}

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

void Renderer::draw(std::string imageName,Vector2 position,Vector2 size) {
        if (images.find(imageName) == images.end()) {
            // Draw an error/default texture here if necessary
            return;
        }

        sf::Sprite sprite;
        sprite.setTexture(images[imageName]);

        // Define the texture rectangle if needed
        sprite.setTextureRect(sf::IntRect(0, 0, images[imageName].getSize().x, images[imageName].getSize().y));

        // Adjust the position
        sprite.setPosition(position.x, position.y);

        // Adjust the size by modifying the scale of the sprite
        sf::FloatRect bounds = sprite.getLocalBounds();
        float scaleX = size.x / bounds.width;
        float scaleY = size.y / bounds.height;
        sprite.setScale(scaleX, scaleY);

        // Draw the sprite in the window
        window.draw(sprite);
    }

void Renderer::drawText(std::string text, std::string fontName, int fontSize, Vector2 pos) {
	sf::Text sfText;
	sfText.setFont(fonts[fontName]);
	sfText.setString(text);
	sfText.setCharacterSize(fontSize);
	sfText.setPosition(pos.x,pos.y);
	window.draw(sfText);
}


Vector2 Renderer::getResolution() {
	sf::Vector2u size = window.getSize();
	return Vector2(size.x, size.y);
}
#endif
