#pragma once

#include "Brain.h"
#include "Blocks.h"

class Agent {
public:

    explicit Agent(int color = 0);

    Agent(const Agent& other);

    ~Agent();

    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] bool isDead() const;

    void bindTo(Block *block);

    void doSomething();

    bool isFriend(Agent* other) const;

    bool isEnemy(Agent* other) const;

    void mutation(double radiation);

private:
    int direction;
    Brain brain;
    double health;
    double energy;
    bool have_food;
    int color;
    Block* block;
};
