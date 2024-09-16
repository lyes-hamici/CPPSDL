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
				Input::keyPressed = name;
				return Input::wasPressed = true;
			}
			else if (!state[scancode] && Input::wasPressed && Input::keyPressed == name)
			{	
				return Input::wasPressed = false;
			}
			else
			{
				return false;
			}
		}
		return false;
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

	bool Input::getPressed(std::string name)
	{
		if (name.empty()){
			return false;
		}
		if (name.length() == 1){
			return getPressed(name[0]);
		}
		if (keys.contains(name))
		{
			if (sf::Keyboard::isKeyPressed(keys[name]) && !Input::wasPressed)
			{
				Input::keyPressed = name;
				return Input::wasPressed = true;
			}
			else if (!sf::Keyboard::isKeyPressed(keys[name]) && Input::wasPressed && Input::keyPressed == name)
			{
				return Input::wasPressed = false;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
#endif
