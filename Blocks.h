#pragma once

#include "Textures.h"
#include <vector>
#include <set>

class Agent;

class Block {
public:
    Block();

    void addNeighbour(Block* neighbour);

    Block* getNeighbour(int direction);

    bool addAgent(Agent* agent);

    void deleteAgent(Agent* agent);

    [[nodiscard]] sf::Sprite getSprite() const;

    bool hasFriend(Agent* agent) const;

    bool hasEnemy(Agent* agent) const;

    [[nodiscard]] bool hasFood() const;

    int getFood();

    Agent* getAnyAgent();

private:
    void updateTexture();

    sf::RenderTexture* texture;
    std::set<Agent*> agents;
    std::vector<Block*> neighbours;
    int food;
};
