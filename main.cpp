#include <SFML/Graphics.hpp>
#include "World.h"
#include <iostream>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "simulated_life");
    World world(80, 80);

    int cnt = 1'000'000;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (cnt >= 0 && cnt % 10'000 == 0) {
            cout << 100 - cnt / 10'000 << "%" << endl;
        }

        --cnt;
        if (cnt < 0) {
            window.clear(sf::Color::Black);

            window.draw(world.getSprite(800, 800));
            world.update();

            sf::sleep(sf::seconds(0.05f));

            window.display();
        } else {
            world.update();
        }
    }
    return 0;
}
