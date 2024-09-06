#include "../include/manual.hpp"
#include "../include/logic_component.hpp"

bool LogicComponent::has_equal_name(string inp_name) {
    return inp_name == name;
}

void LogicComponent::change_name(string new_name) {
    name = new_name;
}

