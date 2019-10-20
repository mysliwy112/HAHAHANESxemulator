#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Machine.h"
#include "ROMloader.h"
#include "RealController.h"


using namespace std;


int main(int argc, char *argv[])
{
    ROM *rom;
    rom=loader::load(argv[1]);

    Machine nesser;
    nesser.insertROM(rom);
    RealController pad1;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        nesser.pad1->readReal(pad1.getPresses());
        nesser.step();
        window.clear();
        window.display();
    }

    return 0;
}
