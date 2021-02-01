#include "World.h"
#include <iostream>

using namespace std;

World::World(int width, int height)
    : width(width)
    , height(height)
    , area(width, vector<Block>(height)){
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            array<int, 4> dx = {1, 0, -1, 0};
            array<int, 4> dy = {0, 1, 0, -1};
            for (int dir = 0; dir < 4; ++dir) {
                auto mod = [](int x, int mod) {
                    if (x >= mod) {
                        return x - mod;
                    }
                    if (x < 0) {
                        return x + mod;
                    }
                    return x;
                };
                int new_x = mod(x + dx[dir], width);
                int new_y = mod(y + dy[dir], height);
                area[x][y].addNeighbour(&area[new_x][new_y]);
            }
        }
    }
    for (int x = 2; x < width; x += 5) {
        for (int y = 2; y < height; y += 5) {
            agents.emplace_back(make_unique<Agent>(&(area[x][y])));
        }
    }
}

sf::Sprite World::getSprite(int sprite_width, int sprite_height) const {
    lock_guard<mutex> guard(render_mutex);
    if (!texture.create(sprite_width, sprite_height)) {
        throw std::runtime_error("couldn't create the world's texture");
    }
    texture.clear(sf::Color(100, 100, 100));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            sf::Sprite sprite = area[x][y].getSprite();
            sf::Vector2 block_size = sprite.getTexture()->getSize();
            sprite.setPosition(static_cast<float>(block_size.x * x),
                               static_cast<float>(block_size.y * y));
            texture.draw(sprite);
        }
    }
    texture.display();
    return sf::Sprite(texture.getTexture());
}

void World::update() {
    for (auto& agent : agents) {
        if (agent->isAlive()) {
            agent->doSomething();
        }
    }
    auto it = remove_if(agents.begin(), agents.end(), [](unique_ptr<Agent>& x) {
        return x->isDead();
    });
    agents.resize(it - agents.begin());
}
