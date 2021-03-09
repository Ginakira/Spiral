//
// Created by Sakata on 2021/3/1.
//

#include <utility>

#include "spiral_handler.h"
#include "spiral_runtime.h"
#include "spiral_parameter.h"
#include "spiral_master.h"
#include "spiral_tree.h"

namespace spiral {

RuntimeEnv::RuntimeEnv(spiral::ASTree &tree) : tree(tree) {}

void RuntimeEnv::run() {
    SParameter p = std::make_shared<Parameter>(nullptr);
    FactoryHandler::init_factory(this->tree);
    RuntimeEnv::getValue(this->tree, p);
}

SIValue RuntimeEnv::getValue(ASTree &tree, SParameter p) {
    IMaster *m = tree.factory->create(tree, std::move(p));
    SIValue val = m->run();
    tree.factory->destroy(m);
    return val;
}

} // namespace spiral