#include "../include/manual.hpp"
#include "../include/errors.hpp"
#include "../include/logic_component.hpp"
#include "../include/base_gate.hpp"
#include "../include/gates.hpp"
#include "../include/module.hpp"

template<typename T>
void show_message(T message) {
    cout << message << endl;
}

vector<string> make_apart(string line_of_file, char separator = ' ') {
    string file_element;
    vector<string> inputs;
    vector<string> result;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator))
        inputs.push_back(file_element);
    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i] != "")
            result.push_back(inputs[i]);
    }
    return result;
}

Module::Module(string logic_name, int num_inputs, vector<shared_ptr<Module>> pre_models)
        : Gate(logic_name), num_of_inputs(num_inputs), created_models(pre_models) {
    vector <string> inp_names;
    for (int i = 0; i < num_inputs; i++)
    {
        inp_names.push_back(INPUTS_NAME + to_string(i));
    }
    initialize_inps_and_outs(inp_names, OUTPUTS_NAME, NULL);
}

int Module::compute() {
    return out->compute();
}

shared_ptr<Gate> Module::copy() {
    shared_ptr<Module> new_logic = make_shared<Module>(name, num_of_inputs, created_models);
    new_logic->inputs.clear();
    for (auto inp: inputs)
    {
        new_logic->inputs.push_back(inp->copy(NULL));
        new_logic->inputs[new_logic->inputs.size()-1]->put(Z);
    }
    new_logic->out = out->copy(NULL);
    new_logic->out->put(Z);
    for (auto new_gate: logics)
        new_logic->logics.push_back(new_gate->copy());
    for (auto pair_wire: connections)
        new_logic->connect_wire(pair_wire.first, pair_wire.second);
    return new_logic; 
}

void Module::change_io_names(string module_id, vector<string> inp_ids, string out_id) {
    Gate::change_io_names(module_id, inp_ids, out_id);
    vector <pair<string, string>> new_names({make_pair(OUTPUTS_NAME, out_id)});
    for (int i = 0; i < num_of_inputs; i++)
        new_names.push_back(make_pair(INPUTS_NAME + to_string(i), inp_ids[i]));
    for (int i = 0; i < connections.size(); i++) {
        for (int j = 0; j < new_names.size(); j++) {
            if (connections[i].first.name == new_names[j].first)
                connections[i].first.name = new_names[j].second;
            if (connections[i].second.name == new_names[j].first)
                connections[i].second.name = new_names[j].second;
        }
    }
}

template<typename T2>
void Module::add_gate(string gate_id, vector<string> inp_ids, string out_id) {
    for (auto pre_gate: logics)
        if (pre_gate->has_equal_name(gate_id))
            throw DuplicatedLogic();
    if (T2::GateType() == NOT_GATE_NAME && inp_ids.size() != 1) 
        throw IncompatibleInputs();
    else if(T2::GateType() != NOT_GATE_NAME && inp_ids.size() < 2)
        throw IncompatibleInputs();
    shared_ptr<Gate> new_logic = make_shared<T2>(gate_id);
    new_logic->initialize_inps_and_outs(inp_ids, out_id, new_logic);
    logics.push_back(new_logic);
}

void Module::add_module(string module_type, string module_id, vector<string> inp_ids, string out_id) {
    bool found = false;
    shared_ptr<Gate> new_module = NULL;
    for (auto my_module: created_models) {
        if (my_module->has_equal_name(module_type)) {
            for (auto pre_gate: logics)
                if (pre_gate->has_equal_name(module_id))
                    throw DuplicatedLogic();
            if (my_module->has_correct_amount_of_inps(inp_ids.size()) == false)
                throw IncompatibleInputs();
            new_module = my_module->copy();
            new_module->change_io_names(module_id, inp_ids, out_id);
            logics.push_back(new_module);
            found = true;
            break;
        }
    }
    if (found == false)
        throw LogicNotFound();
}

shared_ptr<LogicComponent> Module::search_for_wire(bool is_input, bool is_output, string inp_name, int status = ALL) {
    shared_ptr<LogicComponent> found = has_this_wire(is_input, is_output, inp_name);
    if (found != NULL && (status == ALL || status == IO)) {
        return found;
    }
    for (auto element: logics) {
        found = element->has_this_wire(is_input, is_output, inp_name);
        if (found != NULL && (status == ALL || status == GATES)) {
            return found;
        }
    }
    return NULL;
}

void Module::connect_wire(info input_id, info output_id) {
    shared_ptr<LogicComponent> first, second;
    first = search_for_wire(true, true, input_id.name, input_id.status);
    second = search_for_wire(true, true, output_id.name, output_id.status);
    if (first == NULL || second == NULL)
        throw IDNotFound();
    if (first == second)
        throw InvalidConnection();
    first->connect(false, second);
    second->connect(true, first);
    connections.push_back(make_pair(input_id, output_id));
}

void Module::put_amount(string wire_id, int value) {
    shared_ptr<LogicComponent> found = search_for_wire(true, false, wire_id);
    if (found == NULL)
        throw IDNotFound();
    found->put(value);
}

string Module::get_this_logic_output(string logic_ID) {
    int output;
    for (auto my_gate: logics) {
        if (my_gate->has_equal_name(logic_ID)) {
            output = my_gate->compute();
            if (output == ZERO_VALUE | output == ONE_VALUE)
                return to_string(output);
            else
                return Z_STRING;
        }
    }
    throw IDNotFound();
}

bool Module::is_input_name(string wire_name) {
    for (int i = 0; i < num_of_inputs; i++) {
        if (INPUTS_NAME + to_string(i) == wire_name)
            return true;
    }
    return false;
}

void Module::handle_add_commands(vector<string> inputs) {
    if (inputs.size() < 5)
        throw IncompatibleInputs();
    string out_id = inputs.back();
    vector<string> inps_ids(inputs.begin() + 3, inputs.end() - 1);
    if (inputs[1] == AND_GATE_NAME) 
        add_gate<AndGate> (inputs[2], inps_ids, out_id);
    else if (inputs[1] == OR_GATE_NAME) 
        add_gate<OrGate> (inputs[2], inps_ids, out_id); 
    else if (inputs[1] == XOR_GATE_NAME) 
        add_gate<XorGate> (inputs[2], inps_ids, out_id);
    else if (inputs[1] == NAND_GATE_NAME) 
        add_gate<NandGate> (inputs[2], inps_ids, out_id);
    else if (inputs[1] == NOR_GATE_NAME) 
        add_gate<NorGate> (inputs[2], inps_ids, out_id);
    else if (inputs[1] == NOT_GATE_NAME) 
        add_gate<NotGate> (inputs[2], inps_ids, out_id);
    else 
        add_module(inputs[1], inputs[2], inps_ids, out_id);
}

void Module::handle_put_commands(vector<string> inputs) {
    if (inputs.size() < 3)
        return;
    if (inputs[2] != ZERO_STRING && inputs[2] != ONE_STRING)
        throw InvalidValue();
    put_amount(inputs[1], stoi(inputs[2]));
}

void Module::handle_connect_commands(vector<string> inputs) {
    info first, second;
    if (inputs.size() < 3)
        return;
    if (is_input_name(inputs[1]) || inputs[1] == OUTPUTS_NAME)
        first = {inputs[1], IO};
    else 
        first = {inputs[1], GATES};
    if (is_input_name(inputs[2]) || inputs[2] == OUTPUTS_NAME)
        second = {inputs[2], IO};
    else 
        second = {inputs[2], GATES};
    connect_wire(first, second);
}

bool Module::has_correct_amount_of_inps(int amount) {
    return amount == num_of_inputs;
}

vector<shared_ptr<Module>> Module::create_new_model(vector<string> pre_inputs) {  
    if (pre_inputs.size() < 3)
        return created_models;
    for (auto created: created_models)
        if (created->has_equal_name(pre_inputs[1])) 
            throw RepetitiveModule();
    shared_ptr<Module> new_module = make_shared<Module> (pre_inputs[1], stoi(pre_inputs[2]), created_models);
    string line;
    vector<string> inputs;
    while (getline(cin, line)) {
        try {
            inputs = make_apart(line, COMMAND_SEPARATOR);
            if (inputs.size() < 1)
                continue;
            else if (inputs[0] == commands[END_MODULE]) {
                created_models.push_back(new_module);
                break;
            }
            else if (inputs[0] == commands[NEW_MODULE])
                created_models = new_module->create_new_model(inputs);
            else if (inputs[0] == commands[CONNECT])
                new_module->handle_connect_commands(inputs);
            else if (inputs[0] == commands[ADD])
                new_module->handle_add_commands(inputs);
            else if (inputs[0] == commands[PUT])
                new_module->handle_put_commands(inputs);
            else if (inputs[0] == commands[PRINT] && inputs.size() > 1)
                show_message<string> (new_module->get_this_logic_output(inputs[1]));
        }
        catch (Error const &err) {
            show_message<string> (err.what_happened());
        }
    }
    return created_models;
}