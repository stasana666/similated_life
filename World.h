#pragma once

#include "Blocks.h"
#include "Agent.h"
#include <vector>
#include <memory>
#include <mutex>

class World {
public:
    World(int width, int height);

    [[nodiscard]] sf::Sprite getSprite(int sprite_width, int sprite_height) const;

    void update();

private:
    void generateFood();

    int width;
    int height;
    std::vector<std::vector<Block>> area;
    std::vector<std::unique_ptr<Agent>> agents;
    std::vector<std::unique_ptr<Agent>> dead_agents;
    std::vector<double> lifetime;
    int time_of_age;
    mutable sf::RenderTexture texture;
    mutable std::mutex render_mutex;
};
