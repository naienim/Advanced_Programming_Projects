#include "../include/manual.hpp"
#include "../include/logic_component.hpp"
#include "../include/base_gate.hpp"
#include "../include/gates.hpp"

int AndGate::compute() {
    int amount;
    bool is_z= false;
    for (auto inp: inputs) {
        amount = inp->compute();
        if (amount == ZERO_VALUE)
            return ZERO_VALUE;
        else if (amount == Z)
            is_z = true;
    }
    if (is_z == true)
        return Z;
    return ONE_VALUE;
}

shared_ptr<Gate> AndGate::copy() {
    shared_ptr<AndGate> new_logic = make_shared<AndGate>(name);
    for (auto inp: inputs)
        new_logic->inputs.push_back(inp->copy(new_logic));
    new_logic->out = out->copy(new_logic);  
    return new_logic; 
}

int OrGate::compute() {
    int amount;
    bool is_z= false;
    for (auto inp: inputs) {
        amount = inp->compute();
        if (amount == ONE_VALUE)
            return ONE_VALUE;
        else if (amount == Z)
            is_z = true;
    }
    if (is_z == true)
        return Z;
    return ZERO_VALUE;
}

shared_ptr<Gate> OrGate::copy() {
    shared_ptr<OrGate> new_logic = make_shared<OrGate>(name);
    for (auto inp: inputs)
        new_logic->inputs.push_back(inp->copy(new_logic));
    new_logic->out = out->copy(new_logic);  
    return new_logic; 
}

int XorGate::compute() {
    int out;
    vector<int> amounts;
    for (int i = 0; i < inputs.size(); i++) {
        amounts.push_back(inputs[i]->compute());
        if (amounts[i] == Z)
            return Z;
    }
    out = amounts[0];
    for (int i = 1; i < amounts.size(); i++)
        out ^= amounts[i];
    return out;
}

shared_ptr<Gate> XorGate::copy() {
    shared_ptr<XorGate> new_logic = make_shared<XorGate>(name);
    for (auto inp: inputs)
        new_logic->inputs.push_back(inp->copy(new_logic));
    new_logic->out = out->copy(new_logic);  
    return new_logic; 
}

int NotGate::compute() {
    int inp1_amount = inputs[0]->compute();
    if (inp1_amount == Z ) {
        return Z;
    }
    return !inp1_amount;
}

shared_ptr<Gate> NotGate::copy() {
    shared_ptr<NotGate> new_logic = make_shared<NotGate>(name);
    for (auto inp: inputs)
        new_logic->inputs.push_back(inp->copy(new_logic));
    new_logic->out = out->copy(new_logic);  
    return new_logic; 
}

int NandGate::compute() {
    int amount;
    bool is_z= false;
    for (auto inp: inputs) {
        amount = inp->compute();
        if (amount == ZERO_VALUE)
            return ONE_VALUE;
        else if (amount == Z)
            is_z = true;
    }
    if (is_z == true)
        return Z;
    return ZERO_VALUE;
}

shared_ptr<Gate> NandGate::copy() {
    shared_ptr<NandGate> new_logic = make_shared<NandGate>(name);
    for (auto inp: inputs)
        new_logic->inputs.push_back(inp->copy(new_logic));
    new_logic->out = out->copy(new_logic);  
    return new_logic; 
}

int NorGate::compute() {
    int amount;
    bool is_z= false;
    for (auto inp: inputs) {
        amount = inp->compute();
        if (amount == ONE_VALUE)
            return ZERO_VALUE;
        else if (amount == Z)
            is_z = true;
    }
    if (is_z == true)
        return Z;
    return ONE_VALUE;
}

shared_ptr<Gate> NorGate::copy() {
    shared_ptr<NorGate> new_logic = make_shared<NorGate>(name);
    for (auto inp: inputs)
        new_logic->inputs.push_back(inp->copy(new_logic));
    new_logic->out = out->copy(new_logic);  
    return new_logic; 
}