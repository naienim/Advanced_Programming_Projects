#ifndef __LOGIC_COMPONENT__
#define __LOGIC_COMPONENT__

#include "manual.hpp"

class LogicComponent: public enable_shared_from_this<LogicComponent> {
protected:
    string name;
public:
    LogicComponent(string logic_name) : name(logic_name) {}
    bool has_equal_name(string inp_name);
    virtual int compute() = 0;  
    virtual void put(int inp_amount) = 0;
    virtual shared_ptr<LogicComponent> has_this_wire(bool is_input, bool is_output, string inp_name) = 0;
    virtual void connect(bool in_beginning, shared_ptr<LogicComponent> logic) = 0;
    void change_name(string new_name);
};

#endif