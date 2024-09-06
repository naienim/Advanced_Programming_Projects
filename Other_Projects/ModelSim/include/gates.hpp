#ifndef __GATES__
#define __GATES__

#include "manual.hpp"
#include "logic_component.hpp"
#include "base_gate.hpp"

class AndGate : public Gate {
public:
    AndGate(string logic_name): Gate(logic_name) {}
    static const string GateType() { return AND_GATE_NAME;} 
    int compute() override;
    shared_ptr<Gate> copy() override;
};

class OrGate : public Gate {
public:
    OrGate(string logic_name): Gate(logic_name) {}
    static const string GateType() { return OR_GATE_NAME;} 
    int compute() override;
    shared_ptr<Gate> copy() override;
};

class XorGate : public Gate {
public:
    XorGate(string logic_name): Gate(logic_name) {}
    static const string GateType() { return XOR_GATE_NAME;} 
    int compute() override;
    shared_ptr<Gate> copy() override;
};

class NotGate : public Gate {
public:
    NotGate(string logic_name): Gate(logic_name) {}
    static const string GateType() { return NOT_GATE_NAME;} 
    int compute() override;
    shared_ptr<Gate> copy() override;
};

class NandGate : public Gate {
public:
    NandGate(string logic_name): Gate(logic_name) {}
    static const string GateType() { return NAND_GATE_NAME;} 
    int compute() override;
    shared_ptr<Gate> copy() override;
};

class NorGate : public Gate {
public:
    NorGate(string logic_name): Gate(logic_name) {}
    static const string GateType() { return NOR_GATE_NAME;} 
    int compute() override;
    shared_ptr<Gate> copy() override;
};

#endif