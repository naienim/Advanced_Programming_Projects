#include "../include/manual.hpp"
#include "../include/logic_component.hpp"
#include "../include/base_gate.hpp"

Wire::Wire(string logic_name, int wire_type, shared_ptr<LogicComponent> logic, int value= Z): LogicComponent(logic_name) {
    type = wire_type;
    amount = value;
    if (wire_type == INPUT) {
        pre_logic == NULL;
        post_logic == logic;
    }
    else if (wire_type == OUTPUT) {
        pre_logic = logic;
        post_logic = NULL;
    } 
}

shared_ptr<Wire> Wire::copy(shared_ptr<LogicComponent> logic) {
    return make_shared<Wire>(name, type, logic, amount); 
}

shared_ptr<LogicComponent> Wire::has_this_wire(bool is_input, bool is_output, string inp_name) {
    if (has_equal_name(inp_name) && is_input == true && type == INPUT) {
        return shared_from_this();
    }
    else if (has_equal_name(inp_name) && is_output == true && type == OUTPUT) {
        return shared_from_this();
    }
    return NULL;
}

void Wire::connect(bool in_beginning, shared_ptr<LogicComponent> logic) {
    if (in_beginning == true) {
        pre_logic = logic;
    }
    else {
        post_logic = logic;
    }
}

bool Wire::is_connected() {
    if (pre_logic != NULL && type == INPUT) {
        return true;
    }
    else if (post_logic != NULL && type == OUTPUT) {
        return true;
    }
    else {
        return false;
    }
}

int Wire::compute() {
    if (type == OUTPUT && pre_logic != NULL) {
        return pre_logic->compute();
    }
    else if (type == INPUT && is_connected() == true) {
        return pre_logic->compute();
    }
    else {
        return amount;
    }
}

void Wire::put(int inp_amount) {
    amount = inp_amount;
}

void Gate::initialize_inps_and_outs(vector<string> inp_names, string out_name, shared_ptr<LogicComponent> logic) {
    inputs.clear();
    for (auto wire_name: inp_names) {
        inputs.push_back(make_shared<Wire>(wire_name, INPUT, logic));
    }
    out = make_shared<Wire>(out_name, OUTPUT, logic);
}

shared_ptr<LogicComponent> Gate::has_this_wire(bool is_input, bool is_output, string inp_name) {
    for (auto inp: inputs) {
        if (is_input == true) {
            if (inp->has_equal_name(inp_name)) {
                return inp;
            }
        }
    }
    if (is_output == true) {
        if (out->has_equal_name(inp_name)) {
            return out;
        }
    }
    return NULL;
}

void Gate::change_io_names(string module_id, vector<string> inp_ids, string out_id) {
    name = module_id;
    for (int i = 0; i < inp_ids.size(); i++)
        inputs[i]->change_name(inp_ids[i]);
    out->change_name(out_id);
}