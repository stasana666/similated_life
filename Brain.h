#pragma once

#include <vector>
#include <memory>
#include <array>

enum class AgentAction {
    Stay,
    Move,
    Bite,
    Take,
    Eat,
    TurnRight,
    TurnLeft,
    LastElement  // Only for getting size of enum
};

struct DirectionParams {
    bool is_food    = false;
    bool is_enemy   = false;
};

class BrainInput {
public:
    std::array<DirectionParams, 5> area;

    bool have_i_food = false;
    double my_health = 1;
    double energy = 1;

    [[nodiscard]] std::vector<double> getInput() const;

    static int getParamsCount();
};

class Neuron {
public:

    void forwardPropagation();

    void bindTo(Neuron* target);

    [[nodiscard]] double getSignal() const;

    void setSignal(double value);

    void mutation(double radiation);

private:

    static double func(double x);

    struct Synapse {
        Neuron* target;
        double weight;

        Synapse(Neuron* target, double weight);
    };

    std::vector<Synapse> synapses;
    double signal;

    friend class NeuronLayer;
};

class NeuronLayer {
public:
    NeuronLayer();

    NeuronLayer(const NeuronLayer& other);

    void forwardPropagation();

    void clear();

    void bindTo(const std::shared_ptr<NeuronLayer>& target);

    void add();

    void set(const std::vector<double>& value);

    [[nodiscard]] std::vector<double> get() const;

    void mutation(double radiation);

private:
    std::shared_ptr<NeuronLayer> next_layer;
    std::vector<Neuron> layer;
    Neuron bias;

    friend class NeuronNetwork;
};

class NeuronNetwork {
public:
    explicit NeuronNetwork(const std::vector<int>& size_of_levels);

    NeuronNetwork(const NeuronNetwork& other);

    void set(const std::vector<double>& values);

    void forwardPropagation();

    void mutation(double radiation);

    [[nodiscard]] std::vector<double> get() const;

private:
    std::shared_ptr<NeuronLayer> input;
    std::shared_ptr<NeuronLayer> output;
};

class Brain {
public:

    Brain();

    Brain(const Brain& other);

    AgentAction getAction(const BrainInput& input);

    void mutation(double radiation);

private:
    static int getMemorySize();

    std::vector<double> memory;
    NeuronNetwork network;
};
