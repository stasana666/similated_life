#include "Brain.h"
#include "Random.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

void Neuron::forwardPropagation() {
    for (auto [target, weight] : synapses) {
        target->signal += weight * func(signal);
    }
}

void Neuron::bindTo(Neuron *target) {
    synapses.emplace_back(target, 10 * Random::get_random_double() - 5);
}

double Neuron::func(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double Neuron::getSignal() const {
    return func(signal);
}

void Neuron::setSignal(double value) {
    signal = value;
}

void Neuron::mutation(double radiation) {
    for (auto& synapse : synapses) {
        if (Random::get_random_double() < radiation) {
            synapse.weight += (Random::get_random_double() - 0.5) * 2;
        }
    }
}

Neuron::Synapse::Synapse(Neuron *target, double weight)
    : target(target)
    , weight(weight) {
}

NeuronLayer::NeuronLayer()
    : next_layer(nullptr) {
    bias.setSignal(1);
}

void NeuronLayer::forwardPropagation() {
    if (next_layer == nullptr) {
        return;
    }
    next_layer->clear();
    for (auto& neuron : layer) {
        neuron.forwardPropagation();
    }
    next_layer->forwardPropagation();
}

void NeuronLayer::clear() {
    for (auto& neuron : layer) {
        neuron.setSignal(0);
    }
}

void NeuronLayer::bindTo(const shared_ptr<NeuronLayer>& target) {
    if (next_layer != nullptr) {
        throw std::logic_error("NeuronLayer has already binded");
    }
    next_layer = target;
    for (auto& target_neuron : target->layer) {
        for (auto& neuron : layer) {
            neuron.bindTo(&target_neuron);
        }
        bias.bindTo(&target_neuron);
    }
}

void NeuronLayer::add() {
    layer.emplace_back();
    if (next_layer) {
        for (auto& neuron : next_layer->layer) {
            layer.back().bindTo(&neuron);
        }
    }
}

void NeuronLayer::set(const vector<double> &values) {
    if (values.size() != layer.size()) {
        throw runtime_error("");
    }
    for (int i = 0; i < values.size(); ++i) {
        layer[i].setSignal(values[i]);
    }
}

vector<double> NeuronLayer::get() const {
    vector<double> result;
    for (const auto& neuron : layer) {
        result.emplace_back(neuron.getSignal());
    }
    return result;
}

NeuronLayer::NeuronLayer(const NeuronLayer &other)
    : next_layer(nullptr) {
    bias.setSignal(1);
    if (other.next_layer) {
        bindTo(make_shared<NeuronLayer>(*other.next_layer));
        for (size_t i = 0; i < other.layer.size(); ++i) {
            add();
            for (size_t j = 0; j < layer[i].synapses.size(); ++j) {
                layer[i].synapses[j].weight = other.layer[i].synapses[j].weight;
            }
        }
        for (size_t i = 0; i < bias.synapses.size(); ++i) {
            bias.synapses[i].weight = other.bias.synapses[i].weight;
        }
    } else {
        for (size_t i = 0; i < other.layer.size(); ++i) {
            add();
        }
    }
}

void NeuronLayer::mutation(double radiation) {
    for (auto& neuron : layer) {
        neuron.mutation(radiation);
    }
}

NeuronNetwork::NeuronNetwork(const std::vector<int> &size_of_levels) {
    output = make_shared<NeuronLayer>();
    int n = size_of_levels.size();
    if (n <= 1) {
        throw runtime_error("couldn't create neuron network with " + to_string(n) + " layers");
    }
    --n;
    for (int i = 0; i < size_of_levels[n]; ++i) {
        output->add();
    }
    input = output;
    do {
        --n;
        auto ptr = make_shared<NeuronLayer>();
        for (int i = 0; i < size_of_levels[n]; ++i) {
            ptr->add();
        }
        ptr->bindTo(input);
        input = ptr;
    } while (n != 0);
}

void NeuronNetwork::set(const vector<double> &values) {
    input->set(values);
}

void NeuronNetwork::forwardPropagation() {
    input->forwardPropagation();
}

std::vector<double> NeuronNetwork::get() const {
    return output->get();
}

NeuronNetwork::NeuronNetwork(const NeuronNetwork &other) {
    input = make_shared<NeuronLayer>(*other.input);
    output = input;
    while (output->next_layer) {
        output = output->next_layer;
    }
}

void NeuronNetwork::mutation(double radiation) {
    auto ptr = input;
    while (ptr != output) {
        ptr->mutation(radiation);
        ptr = ptr->next_layer;
    }
}

Brain::Brain()
    : network({BrainInput::getParamsCount() + getMemorySize(),
               static_cast<int>(AgentAction::LastElement) + getMemorySize()})
    , memory(getMemorySize()) {
}

Brain::Brain(const Brain &other)
    : network(other.network)
    , memory(getMemorySize()) {
}

AgentAction Brain::getAction(const BrainInput& params) {
    vector<double> input = params.getInput();

    for (auto i : memory) {
        input.emplace_back(i);
    }

    network.set(input);
    network.forwardPropagation();
    vector<double> output = network.get();

    copy(output.begin() + static_cast<int>(AgentAction::LastElement),
         output.end(),
         memory.begin());

    AgentAction result = AgentAction::Stay;
    double max_value = output[static_cast<int>(AgentAction::Stay)];

    for (int i = 0; i < static_cast<int>(AgentAction::LastElement); ++i) {
        if (max_value < output[i]) {
            max_value = output[i];
            result = static_cast<AgentAction>(i);
        }
    }

    return result;
}

int Brain::getMemorySize() {
    return 2;
}

void Brain::mutation(double radiation) {
    network.mutation(radiation);
}

int BrainInput::getParamsCount() {
    return 13;
}

std::vector<double> BrainInput::getInput() const {
    vector<double> result;

    for (int dir = 0; dir < 5; ++dir) {
        result.emplace_back(area[dir].is_enemy);
        result.emplace_back(area[dir].is_food);
    }

    result.emplace_back(have_i_food);
    result.emplace_back(my_health);
    result.emplace_back(energy);

    return result;
}
