//
// Created by Sakata on 2021/3/1.
//

#include "spiral_handler.h"
#include "spiral_runtime.h"
#include "spiral_parameter.h"
#include "spiral_master.h"
#include "spiral_tree.h"

namespace spiral {

RuntimeEnv::RuntimeEnv(spiral::ASTree &tree) : tree(tree) {}

void RuntimeEnv::run() {
    auto *p = new Parameter(nullptr);
    FactoryHandler::init_factory(this->tree);
    RuntimeEnv::getValue(this->tree, p);
    delete p;
}

IValue *RuntimeEnv::getValue(ASTree &tree, Parameter *p) {
    IMaster *m = tree.factory->create(tree, p);
    IValue *val = m->run();
    tree.factory->destroy(m);
    return val;
}

} // namespace spiral