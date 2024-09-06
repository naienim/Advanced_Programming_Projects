#include "../include/manual.hpp"
#include "../include/errors.hpp"
#include "../include/logic_component.hpp"
#include "../include/base_gate.hpp"
#include "../include/gates.hpp"
#include "../include/module.hpp"
#include "../include/model_sim.hpp"

ModelSim::ModelSim()
{
    vector<shared_ptr<Module>> created_models;
    circuit = make_shared<Module>(PROGRAM_NAME, 0, created_models);
}

void ModelSim::handle_connect_commands(vector<string> inputs) {
    if (inputs.size() < 3)
        return;
    circuit->connect_wire({inputs[1], GATES}, {inputs[2], GATES});
}

void ModelSim::get_input() {
    string line;
    vector<string> inputs;
    while (getline(cin, line)) {
        try {
            inputs = make_apart(line, COMMAND_SEPARATOR);
            if (inputs.size() <= 1)
                continue;
            else if (inputs[0] == commands[NEW_MODULE])
                circuit->create_new_model(inputs);
            else if (inputs[0] == commands[CONNECT])
                handle_connect_commands(inputs);
            else if (inputs[0] == commands[ADD])
                circuit->handle_add_commands(inputs);
            else if (inputs[0] == commands[PUT])
                circuit->handle_put_commands(inputs);
            else if (inputs[0] == commands[PRINT])
                show_message<string> (circuit->get_this_logic_output(inputs[1]));
        }
        catch (Error const &err) {
            show_message<string> (err.what_happened());
        }
    }
}