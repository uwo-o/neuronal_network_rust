#include "network.h"

Network::Network(int input_size, int neurons_per_hlayer, int hlayers_size, int output_size, double learning_rate) {
    this->network = new Layer*[hlayers_size + 2];
    this->layers = hlayers_size + 2;
    this->learning_rate = learning_rate;
    this->input_size = input_size;
    this->hlayers_size = hlayers_size;
    this->output_size = output_size;

    std::cout << "Creating network with " << hlayers_size << " hidden layers" << std::endl;

    for (int i = 0; i < hlayers_size + 2; i++) {
        if (i == 0) {
            this->network[i] = new Layer(i, input_size, input_size);
        } else if (i == hlayers_size + 1) {
            if (hlayers_size == 0) {
                this->network[i] = new Layer(i, output_size, input_size);
            } else {
                this->network[i] = new Layer(i, output_size, neurons_per_hlayer);
            }
        } else if(i == 1) {
            this->network[i] = new Layer(i, neurons_per_hlayer, input_size);
        } else {
            this->network[i] = new Layer(i, neurons_per_hlayer, neurons_per_hlayer);
        }
    }

    std::cout << "Network created!" << std::endl;
}

Network::~Network() {
    for (int i = 0; i < layers; i++) {
        delete this->network[i];
    }
    delete[] this->network;
}

void Network::set_name(std::string name) {
    this->name = name;
}

std::string Network::get_name() {
    return this->name;
}

void Network::describe() {
    std::cout << "Network description\n" << std::endl,
    std::cout << "Network: " << this->name << std::endl;
    std::cout << "Input size: " << this->input_size << std::endl;
    std::cout << "Hidden layers: " << this->hlayers_size << std::endl;
    std::cout << "Output size: " << this->output_size << std::endl;
    std::cout << "Learning rate: " << this->learning_rate << std::endl;
}

void Network::fdescribe() {
    this->describe();
    for (int i = 0; i < layers; i++) {
        this->network[i]->print();
    }
}

Layer * Network::get_layer(int id) {
    return this->network[id];
}

int Network::get_layers_size() {
    return this->layers;
}

void Network::set_activation(double (activation)(double)) {
    this->activation = activation;
}

double (*Network::get_activation())(double) {
    return this->activation;
}

void Network::set_d_activation(double (dactivation)(double)) {
    this->d_activation = dactivation;
}

double (*Network::get_d_activation())(double) {
    return this->d_activation;
}