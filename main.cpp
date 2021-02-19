#include <SFML/Graphics.hpp>
#include "World.h"
#include <iostream>

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 800), "simulated_life");
    World world(80, 80);

    const int START_CNT = 100'000;
    bool isSpacePressed = false;
    int cnt = -1;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            isSpacePressed = true;
        } else {
            if (isSpacePressed) {
                isSpacePressed = false;
                cnt = START_CNT;
            }
        }

        if (cnt >= 0 && cnt % (START_CNT / 100) == 0) {
            cout << 100 - cnt / (START_CNT / 100) << "%" << endl;
        }

        --cnt;
        if (cnt < 0) {
            window.clear(sf::Color::Black);

            window.draw(world.getSprite(800, 800));
            world.update();

            sleep(seconds(0.1f));

            window.display();
        } else {
            world.update();
        }
    }
    return 0;
}
