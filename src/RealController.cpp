#include <SFML/Window.hpp>

#include "RealController.h"

RealController::RealController()
{
    keycodes.resize(8);
    keycodes[0]=sf::Keyboard::Z;
    keycodes[1]=sf::Keyboard::B;
    keycodes[2]=sf::Keyboard::A;
    keycodes[3]=sf::Keyboard::S;
    keycodes[4]=sf::Keyboard::Up;
    keycodes[5]=sf::Keyboard::Down;
    keycodes[6]=sf::Keyboard::Left;
    keycodes[7]=sf::Keyboard::Right;
}

RealController::~RealController()
{
    //dtor
}

vector<int> RealController::getPresses()
{
    vector<int> states(keycodes.size());
    for(int i=0;i<keycodes.size();i++){
        if (sf::Keyboard::isKeyPressed(keycodes[i])){
            states[i]=1;
        }else{
            states[i]=0;
        }
    }
    return states;
}

void RealController::setKeycodes(vector<sf::Keyboard::Key>keys)
{
    keycodes=keys;
}
