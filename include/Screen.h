#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen
{
    public:
        Screen();
        virtual ~Screen();
        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;

    protected:

    private:
};

#endif // SCREEN_H
