//
// Created by Sakata on 2021/3/1.
//

#include <cstdio>

#include "SpiralParser.h"

#include "spiral_runtime.h"
#include "spiral_parameter.h"
#include "spiral_visitor.h"
#include "spiral_tree.h"

namespace spiral {

IMaster::IMaster(ASTree &tree, Parameter *p) : tree(tree), p(p) {}

PrintMaster::PrintMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

ExprMaster::ExprMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

BlockMaster::BlockMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

void IMaster::IFactory::destroy(IMaster *m) {
    delete m;
}

IValue *PrintMaster::run() {
    if (tree.type() != PRINT) {
        throw std::runtime_error("Tree type is not print. PrintMaster::run()");
    }
    for (int i = 0, n = this->tree.size(); i < n; ++i) {
        auto child_tree = this->tree.at(i);
        IValue *ret = RuntimeEnv::getValue(child_tree, this->p);
        ConvertToStringVisitor vis;
        ret->accept(&vis);
        if (i) printf(" ");
        printf("%s", vis.result().c_str());
    }
    printf("\n");
    return spiral::null_val;
}

IValue *ExprMaster::run() {
    switch (this->tree.type()) {
        case INT: {
            const char *s = this->tree.text().c_str();
            int val_int;
            sscanf(s, "%d", &val_int);
            return new IntValue(val_int);
        }
        case ID: {
            return this->p->get(this->tree.text());
        }
        case PLUS: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) + (*b);
        }
        case MINUS: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) - (*b);
        }
        case TIMES: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) * (*b);
        }
        case ASSIGN: {
            std::string name = tree.at(0).text();
            IValue *val = RuntimeEnv::getValue(tree.at(1), this->p);
            this->p->set(name, val);
            return val;
        }
        case DEF: {
            for (int i = 0, n = this->tree.size(); i < n; ++i) {
                std::string name = this->tree.at(i).text();
                this->p->define_param(name);
                IValue *val = spiral::null_val;
                if (this->tree.at(i).size() > 0) {
                    val = RuntimeEnv::getValue(this->tree.at(i).at(0), this->p);
                }
                this->p->set(name, val);
            }
            return spiral::null_val;
        }
        default:
            throw std::runtime_error("Tree type is not expr. ExprMaster::run()");
    }
    return spiral::null_val;
}

IValue *BlockMaster::run() {
    if (tree.type() != BLOCK) {
        throw std::runtime_error("Tree type is not block. BlockMaster::run()");
    }
    auto *new_p = new Parameter(this->p);
    for (int i = 0, n = this->tree.size(); i < n; ++i) {
        auto child_tree = this->tree.at(i);
        RuntimeEnv::getValue(child_tree, new_p);
    }
    delete new_p;
    return spiral::null_val;
}


} // namespace spiral