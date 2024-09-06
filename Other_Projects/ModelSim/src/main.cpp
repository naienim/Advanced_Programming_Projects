#include "../include/manual.hpp"
#include "../include/errors.hpp"
#include "../include/logic_component.hpp"
#include "../include/base_gate.hpp"
#include "../include/gates.hpp"
#include "../include/module.hpp"
#include "../include/model_sim.hpp"

int main() {
    shared_ptr<ModelSim> program = make_shared<ModelSim> ();
    program->get_input();

    return 0;
}



