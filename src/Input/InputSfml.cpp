#include <map>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <cctype>
#include <iostream>
#include <thread> // pour std::this_thread::sleep_for
#include <chrono> // pour std::chrono::milliseconds


class InputSfml
{
public:
    static void initializeSfml();
    static bool getPressed(const std::string& name);
    static bool getPressed(char character);
    static std::map<std::string, sf::Keyboard::Key> keys;
};

std::map<std::string, sf::Keyboard::Key> InputSfml::keys;

void InputSfml::initializeSfml()
{
    keys["Left"] = sf::Keyboard::Left;
    keys["Right"] = sf::Keyboard::Right;
    keys["Up"] = sf::Keyboard::Up;
    keys["Down"] = sf::Keyboard::Down;
    keys["Escape"] = sf::Keyboard::Escape;
}

bool InputSfml::getPressed(char character)
{
    if (!std::isalpha(character)) 
    {
        return false;
    }
    character = std::toupper(character);
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(character - 'A' + sf::Keyboard::A));
}

bool InputSfml::getPressed(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }

    if (name.length() == 1){

        return getPressed(name[0]);
    }
    
    // Vérifier si c'est une touche nommée (par ex. "Left", "Escape", etc.)
    bool exists = keys.contains(name);

    
    return exists ? sf::Keyboard::isKeyPressed(keys[name]) : false;
    

    // Sinon, traiter comme une touche de caractère unique
    
}

int main()
{
    InputSfml::initializeSfml();
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (InputSfml::getPressed("Escape"))
        {
            std::cout << "Closing Program" << std::endl;
            break;
        }
        if (InputSfml::getPressed("Left"))
        {
            std::cout << "Shifting to the left" << std::endl;
        }
        if (InputSfml::getPressed("Right"))
        {
            std::cout << "Shifting to the Right" << std::endl;
        }
        if (InputSfml::getPressed("Up"))
        {
            std::cout << "UPPPPPPP" << std::endl;
        }
        if (InputSfml::getPressed("Down"))
        {
            std::cout << "GET DOWWWNN" << std::endl;
        }
        if (InputSfml::getPressed('r'))
        {
            std::cout << "REPLAYMOTHERFUCKER" << std::endl;
        }
    }
    return 0;
}
