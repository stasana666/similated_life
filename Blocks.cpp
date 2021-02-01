#include "Blocks.h"
#include "Agent.h"
#include <algorithm>
#include <iostream>

void Block::addNeighbour(Block* neighbour) {
    neighbours.emplace_back(neighbour);
}

bool Block::addAgent(Agent* agent) {
    if (!agents.empty()) {
        return false;
    }
    agents.insert(agent);
    updateTexture();
    return true;
}

void Block::deleteAgent(Agent *agent) {
    agents.erase(agent);
    updateTexture();
}

sf::Sprite Block::getSprite() const {
    return sf::Sprite(texture->getTexture());
}

Block *Block::getNeighbour(int direction) {
    return neighbours[direction];
}

bool Block::hasFriend(Agent* agent) const {
    return std::any_of(agents.begin(), agents.end(), [agent](auto i) {
        return i->isFriend(agent);
    });
}

bool Block::hasEnemy(Agent *agent) const {
    return std::any_of(agents.begin(), agents.end(), [agent](auto i) {
        return i->isEnemy(agent);
    });
}

bool Block::hasFood() const {
    return food != 0;
}

int Block::getFood() {
    if (food == 0) {
        return 0;
    }
    --food;
    updateTexture();
    return 1;
}

Agent *Block::getAnyAgent() {
    if (agents.empty()) {
        return nullptr;
    }
    return *agents.begin();
}

void Block::updateTexture() {
    texture = Textures::empty.get();
    if (food) {
        texture = Textures::food.get();
    }
    if (!agents.empty()) {
        texture = Textures::agent.get();
    }
}

Block::Block()
    : texture(nullptr)
    , food(0) {
    updateTexture();
}
