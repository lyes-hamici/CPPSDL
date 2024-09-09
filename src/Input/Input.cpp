#include "Input.hpp"
#ifdef USE_WINDOWSCONSOLE
	#include <windows.h>
	#include <cctype>
	#include <iostream>
	std::map<std::string, int> Input::keys;
	bool Input::wasPressed = false;

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
			if (!(Input::wasPressed) && state & WM_KEYDOWN)
			{
				return Input::wasPressed = true;
			}
			else if (Input::wasPressed && state & WM_KEYUP)
			{
				return Input::wasPressed = false;
			}
			return false;
		}
		return Input::getPressed(name[0]);
	}
#endif
#ifdef USE_SDL

#endif
#ifdef USE_SFML
	#include <map>
	#include <string>
	#include <SFML/Window/Keyboard.hpp>
	#include <cctype>
	#include <iostream>
	#include <thread> // pour std::this_thread::sleep_for
	#include <chrono> // pour std::chrono::milliseconds

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