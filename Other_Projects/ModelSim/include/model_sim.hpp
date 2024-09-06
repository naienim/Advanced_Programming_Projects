#ifndef __MODEL_SIM__
#define __MODEL_SIM__

#include "manual.hpp"
#include "errors.hpp"
#include "logic_component.hpp"
#include "base_gate.hpp"
#include "gates.hpp"
#include "module.hpp"

class ModelSim {
private:
    shared_ptr<Module> circuit;
public:
    ModelSim();
    void get_input();
    void handle_connect_commands(vector<string> inputs);
};

#endif