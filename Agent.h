#pragma once

#include "Brain.h"
#include "Blocks.h"

class Agent {
public:

    explicit Agent(Block* block, int color = 0);

    ~Agent();

    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] bool isDead() const;

    void doSomething();

    bool isFriend(Agent* other) const;

    bool isEnemy(Agent* other) const;

private:
    int direction;
    Brain brain;
    double health;
    double energy;
    bool have_food;
    int color;
    Block* block;
};
