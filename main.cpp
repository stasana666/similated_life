#include <SFML/Graphics.hpp>
#include "World.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "simulated_life");
    World world(30, 30);

    int cnt = 100'000;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (cnt < 0) {
            window.clear(sf::Color::Black);

            window.draw(world.getSprite(600, 600));
            world.update();

            sf::sleep(sf::seconds(0.2f));

            window.display();
        } else {
            --cnt;
            world.update();
        }
    }
    return 0;
}
