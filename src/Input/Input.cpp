#include "Input.hpp"

bool Input::wasPressed = false;
std::string Input::keyPressed;

#ifdef USE_WINDOWSCONSOLE

std::map<std::string, int> Input::keys;

void Input::initialize()
{
	Input::keys["Left"] = VK_LEFT;
	Input::keys["Right"] = VK_RIGHT;
	Input::keys["Up"] = VK_UP;
	Input::keys["Down"] = VK_DOWN;
	Input::keys["Escape"] = VK_ESCAPE;
	Input::keys["Return"] = VK_RETURN;
	}

	bool Input::getPressed(char character){
		if(!std::isalpha(character)){return false;}
		int state = GetKeyState(std::toupper(character));
		if(state & WM_KEYDOWN){return true;}
		if(state & WM_KEYUP){return false;}
		return false;
	}
	bool Input::getPressed(std::string name)
	{
		// std::cout << std::boolalpha << "On entering getPressed - wasPressed : " << Input::wasPressed << std::endl;
		if (name.length() < 1)
		{
			return false;
		}
		int state = 0;
		if (name.length() > 1 && Input::keys.contains(name))
		{
			state = GetKeyState(Input::keys[name]);
			if (!(Input::wasPressed) && (state & WM_KEYDOWN))
			{
				Input::keyPressed = name;
				return Input::wasPressed = true;
			}
			else if ((Input::wasPressed) && !(state & WM_KEYDOWN) && (Input::keyPressed == name))
			{
				return Input::wasPressed = false;
			}
			return false;
		}
		return Input::getPressed(name[0]);
	}
#endif
#ifdef USE_SDL

	std::map<std::string, SDL_KeyCode> Input::keys;

	void Input::initialize()
	{
		// Testing Block
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_Window *window = SDL_CreateWindow("Ma Fenêtre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			std::cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
		{
			std::cerr << "Erreur lors de la création du renderer: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		// End Testing Block
		Input::keys["Left"] = SDLK_LEFT;
		Input::keys["Right"] = SDLK_RIGHT;
		Input::keys["Up"] = SDLK_UP;
		Input::keys["Down"] = SDLK_DOWN;
		Input::keys["Escape"] = SDLK_ESCAPE;
		Input::keys["Return"] = SDLK_RETURN;
		Input::keys["r"] = SDLK_r;
	}

	bool Input::getPressed(char character)
	{
		return false;
	}

	bool Input::getPressed(std::string name)
	{
		if (name.empty())
		{
			return false;
		}

		if (Input::keys.contains(name))
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			SDL_Scancode scancode = SDL_GetScancodeFromKey(Input::keys[name]);
			SDL_PumpEvents();
			if (state[scancode] && !Input::wasPressed)
			{
				Input::wasPressed = true;
				Input::keyPressed = Input::keys[name];
				SDL_PumpEvents();
				return true;
			}
			else if (!state[scancode] && Input::wasPressed && Input::keyPressed == InputSDL::keys[name])
			{
				Input::wasPressed = false;
				SDL_PumpEvents();
				return false;
			}
			else
			{
				SDL_PumpEvents();
				return false;
			}
		}
	}
#endif

#ifdef USE_SFML
	std::map<std::string, sf::Keyboard::Key> Input::keys;

	void Input::initialize()
	{
		keys["Left"] = sf::Keyboard::Left;
		keys["Right"] = sf::Keyboard::Right;
		keys["Up"] = sf::Keyboard::Up;
		keys["Down"] = sf::Keyboard::Down;
		keys["Escape"] = sf::Keyboard::Escape;
	}

	bool Input::getPressed(char character)
	{
		if (!std::isalpha(character)) 
		{
			return false;
		}
		character = std::toupper(character);
		return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(character - 'A' + sf::Keyboard::A));
	}

	bool Input::getPressed(const std::string& name)
	{
		if (name.empty()){
			return false;
		}
		if (name.length() == 1){
			return getPressed(name[0]);
		}
		// Vérifier si c'est une touche nommée (par ex. "Left", "Escape", etc.)
		return keys.contains(name) ? sf::Keyboard::isKeyPressed(keys[name]) : false;
		// Sinon, traiter comme une touche de caractère unique
	}
#endif


// int main()
// {
//     Input::initialize();
//     while(true)
//     {
//         Sleep(100);
//         // system("cls");
//         if (Input::getPressed("Escape"))
//         {
//             std::cout << "Closing Programm" << std::endl;
//             return 0;
//         }
//         if (Input::getPressed("Left"))
//         {
//             std::cout << "Shifting to the left" << std::endl;
//         }
//         if (Input::getPressed("Right"))
//         {
//             std::cout << "Shifting to the Right" << std::endl;
//         }
//         if (Input::getPressed("Up"))
//         {
//             std::cout << "UPPPPPPP" << std::endl;
//         }
//         if (Input::getPressed("Down"))
//         {
//             std::cout << "GET DOWWWNN" << std::endl;
//         }
//         if (Input::getPressed("Return"))
//         {
//             std::cout << "Retour" << std::endl;
//         }
//         if (Input::getPressed("r"))
//         {
//             std::cout << "REPLAYMOTHERFUCKER" << std::endl;
//         }
//     }
//     return 0;
// }