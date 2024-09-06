#ifndef __BASE_GATE__
#define __BASE_GATE__

#include "manual.hpp"
#include "logic_component.hpp"

class Wire : public LogicComponent {
private:
    int amount;
    int type;
    shared_ptr<LogicComponent> pre_logic , post_logic;
public:
    Wire(string logic_name, int wire_type, shared_ptr<LogicComponent>, int value); 
    shared_ptr<Wire> copy(shared_ptr<LogicComponent> logic);  
    shared_ptr<LogicComponent> has_this_wire(bool is_input, bool is_output, string inp_name) override;
    void connect(bool in_beginning, shared_ptr<LogicComponent> logic) override;
    void put(int inp_amount) override;
    int compute() override;
    bool is_connected();
};

class Gate : public LogicComponent {
protected:
    vector<shared_ptr<Wire>> inputs;
    shared_ptr<Wire> out;
public:
    Gate(string logic_name): LogicComponent(logic_name) {};
    void initialize_inps_and_outs(vector<string> inp_names, string out_name, shared_ptr<LogicComponent>);
    virtual int compute() = 0;
    virtual shared_ptr<Gate> copy() = 0;
    void put(int inp_amount) override {};
    shared_ptr<LogicComponent> has_this_wire(bool is_input, bool is_output, string inp_name) override;
    void connect(bool in_beginning, shared_ptr<LogicComponent> logic) override {};
    virtual void change_io_names(string module_id, vector<string> inp_ids, string out_id);
};

#endif