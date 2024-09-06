#ifndef __MODULE__
#define __MODULE__

#include "manual.hpp"
#include "errors.hpp"
#include "logic_component.hpp"
#include "base_gate.hpp"
#include "gates.hpp"

template<typename T>
void show_message(T message);

vector<string> make_apart(string line_of_file, char separator);

class Module : public Gate {
protected:
    vector<shared_ptr<Gate>> logics;
    vector<shared_ptr<Module>> created_models;
    vector<pair<info, info>> connections;
    int num_of_inputs;
public:
    Module(string logic_name, int num_inputs, vector<shared_ptr<Module>> pre_models);
    int compute() override;
    shared_ptr<Gate> copy() override;
    void change_io_names(string module_id, vector<string> inp_ids, string out_id) override;
    template<typename T>
    void add_gate(string gate_id, vector<string> inp_ids, string out_id);
    void add_module(string module_type, string module_id, vector<string> inp_ids, string out_id);
    shared_ptr<LogicComponent> search_for_wire(bool is_input, bool is_output, string inp_name, int status);
    void connect_wire(info wire1, info wire2);
    void put_amount(string wire_id, int value);
    vector<shared_ptr<Module>> create_new_model(vector<string> pre_inputs);
    string get_this_logic_output(string logic_ID);
    bool is_input_name(string wire_name);
    void handle_add_commands(vector<string> inputs);
    void handle_put_commands(vector<string> inputs);
    void handle_connect_commands(vector<string> inputs);
    bool has_correct_amount_of_inps(int amount);
};

#endif