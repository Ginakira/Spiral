//
// Created by Sakata on 2021/3/1.
//

#include <cstdio>
#include <spiral_master.h>

#include "spiral_runtime.h"
#include "spiral_parameter.h"
#include "spiral_visitor.h"
#include "spiral_tree.h"
#include "spiral_util.h"

namespace spiral {

IMaster::IMaster(ASTree &tree, Parameter *p) : tree(tree), p(p) {}

PrintMaster::PrintMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

ExprMaster::ExprMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

BlockMaster::BlockMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

ConditionMaster::ConditionMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

ControlMaster::ControlMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

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
        case FLOAT: {
            const char *s = this->tree.text().c_str();
            double val_float;
            sscanf(s, "%lf", &val_float);
            return new FloatValue(val_float);
        }
        case STRING: {
            // Escape character
            // eg: 'h' 'e' 'l' 'l' 'o' '\' 'n' -> 'h' 'e' 'l' 'l' 'o' '\n'
            std::string val = ConvertStringToCString(this->tree.text());
            return new StringValue(val.substr(1, val.size() - 2));
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
        case NOPE: {
            return spiral::true_val;
        }
        default:
            throw std::runtime_error("Tree type is not expr. ExprMaster::run()");
    }
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

IValue *ConditionMaster::run() {
    switch (this->tree.type()) {
        case OR: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            if (a->isTrue()) {
                return spiral::true_val;
            }
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return b->isTrue() ? spiral::true_val : spiral::false_val;
        }
        case AND: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            if (a->isFalse()) {
                return spiral::false_val;
            }
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return b->isTrue() ? spiral::true_val : spiral::false_val;
        }
        case EQ: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) == (*b) ? spiral::true_val : spiral::false_val;
        }
        case NE: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) != (*b) ? spiral::true_val : spiral::false_val;
        }
        case GT: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) > (*b) ? spiral::true_val : spiral::false_val;
        }
        case GE: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) >= (*b) ? spiral::true_val : spiral::false_val;
        }
        case LITTLE: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) < (*b) ? spiral::true_val : spiral::false_val;
        }
        case LE: {
            IValue *a = RuntimeEnv::getValue(this->tree.at(0), this->p);
            IValue *b = RuntimeEnv::getValue(this->tree.at(1), this->p);
            return (*a) <= (*b) ? spiral::true_val : spiral::false_val;
        }
        default: {
            throw std::runtime_error("Tree type is not condition. ConditionMaster::run()");
        }
    }
}

IValue *ControlMaster::run() {
    switch (this->tree.type()) {
        case IF: {
            IValue *condition_val = RuntimeEnv::getValue(this->tree.at(0), this->p);
            if (condition_val->isTrue()) {
                RuntimeEnv::getValue(this->tree.at(1), this->p);
            } else if (this->tree.size() == 3) {
                RuntimeEnv::getValue(this->tree.at(2), this->p);
            }
            return spiral::null_val;
        }
        case FOR: {
            this->p = new Parameter(p);
            for (RuntimeEnv::getValue(this->tree.at(0), this->p);
                 RuntimeEnv::getValue(this->tree.at(1), this->p)->isTrue();
                 RuntimeEnv::getValue(this->tree.at(2), this->p)) {
                RuntimeEnv::getValue(this->tree.at(3), this->p);
            }
            this->p = this->p->next();
            return spiral::null_val;
        }
        case WHILE: {
            while (RuntimeEnv::getValue(this->tree.at(0), this->p)->isTrue()) {
                RuntimeEnv::getValue(this->tree.at(1), this->p);
            }
            return spiral::null_val;
        }
        case DOWHILE: {
            do {
                RuntimeEnv::getValue(this->tree.at(1), this->p);
            } while (RuntimeEnv::getValue(this->tree.at(0), this->p)->isTrue());
            return spiral::null_val;
        }
        default:
            throw std::runtime_error("Tree type is not control. ControlMaster::run()");
    }
}

} // namespace spiral