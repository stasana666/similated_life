#include "Agent.h"

Agent::Agent(Block* block, int color)
    : direction(0)
    , brain()
    , health(1)
    , have_food(false)
    , color(color)
    , block(block) {
    block->addAgent(this);
}

bool Agent::isAlive() const {
    return health > 0;
}

void Agent::doSomething() {
    if (energy < 0) {
        health += energy;
    }
    BrainInput input;
    auto mod = [](int x, int mod) {
        if (x >= mod) {
            return x - mod;
        }
        if (x < 0) {
            return x + mod;
        }
        return x;
    };
    for (int dir = 0; dir < 4; ++dir) {
        Block* near_block = block->getNeighbour(mod(direction + dir, 4));
        DirectionParams direction_params;
        direction_params.is_friend   = near_block->hasFriend(this);
        direction_params.is_enemy    = near_block->hasEnemy(this);
        direction_params.is_food     = near_block->hasFood();
        input.area[dir] = direction_params;
    }
    input.have_i_food = have_food;
    input.my_health = health;

    AgentAction action = brain.getAction(input);
    switch (action) {
        case AgentAction::TurnLeft:
            energy -= 0.05;
            direction = mod(direction - 1, 4);
            break;
        case AgentAction::TurnRight:
            energy -= 0.05;
            direction = mod(direction + 1, 4);
            break;
        case AgentAction::Take:
            energy -= 0.05;
            if (have_food) {
                break;
            }
            have_food = block->getFood();
            break;
        case AgentAction::Eat:
            if (!have_food) {
                break;
            }
            energy += 0.5;
        case AgentAction::Move:
            energy -= 0.075;
            {
                Block *next_block = block->getNeighbour(direction);
                if (next_block->addAgent(this)) {
                    block->deleteAgent(this);
                    block = next_block;
                }
            }
            break;
        case AgentAction::Bite:
            energy -= 0.09;
            {
                Block* target_block = block->getNeighbour(direction);
                Agent* target = target_block->getAnyAgent();
                if (target != nullptr) {
                    target->health -= 0.1;
                }
            }
            break;
        case AgentAction::Stay:
            energy -= 0.025;
            break;
    }
}

bool Agent::isFriend(Agent *other) const {
    return color == other->color;
}

bool Agent::isEnemy(Agent *other) const {
    return color != other->color;
}

Agent::~Agent() {
    block->deleteAgent(this);
}

bool Agent::isDead() const {
    return health <= 0;
}
