#include "Input.hpp"

#include <windows.h>
#include <cctype>
#include <iostream>


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
    int state = WM_KEYUP;
    if (name.length() > 1 && Input::keys.contains(name))
    {
        state = GetKeyState(Input::keys[name]);
        if (state & WM_KEYDOWN)
        {
            return true;
        }
        if (state & WM_KEYUP)
        {
            return false;
        }
        return false;
    }
    return Input::getPressed(name[0]);
}

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