//
// Created by Sakata on 2021/2/28.
//

#include <stdexcept>

#include "spiral_parameter.h"
#include "spiral_type.h"

namespace spiral {

Parameter::Parameter(Parameter *next) : _next(next) {}

void Parameter::define_param(const string &name) {
    if (this->memory.find(name) != this->memory.end()) {
        throw std::runtime_error("Variable '" + name + "' re-defined!");
    }
    this->memory[name] = spiral::null_val;
}

IValue *Parameter::get(const string &name) const {
    if (this->memory.find(name) == this->memory.end()) {
        if (this->next() == nullptr) {
            throw std::runtime_error("Variable '" + name + "' undefined!");
        }
        return this->next()->get(name);
    }
    return this->memory[name];
}

void *Parameter::set(const string &name, IValue *val) {
    if (this->memory.find(name) == this->memory.end()) {
        if (this->next() == nullptr) {
            throw std::runtime_error("Variable '" + name + "' undefined!");
        }
        return this->next()->set(name, val);
    }
    return this->memory[name] = val;
}

Parameter *Parameter::next() const {
    return this->_next;
}

} // namespace spiral