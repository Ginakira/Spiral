//
// Created by Sakata on 2021/2/28.
//

#include <stdexcept>
#include <utility>

#include "spiral_parameter.h"
#include "spiral_type.h"

namespace spiral {

Parameter::Parameter(SParameter next, int position) : _next(std::move(next)), _position(position) {}

void Parameter::define_param(const string &name) {
    if (this->memory.find(name) != this->memory.end()) {
        throw std::runtime_error("Variable '" + name + "' re-defined!");
    }
    this->memory[name] = spiral::null_val;
}

SIValue Parameter::get(const string &name) const {
    if (this->memory.find(name) == this->memory.end()) {
        if (this->next() == nullptr) {
            throw std::runtime_error("Variable '" + name + "' undefined!");
        }
        return this->next()->get(name);
    }
    return this->memory[name];
}

void Parameter::set(const string &name, const SIValue &val) {
    if (this->memory.find(name) == this->memory.end()) {
        if (this->next() == nullptr) {
            throw std::runtime_error("Variable '" + name + "' undefined!");
        }
        return this->next()->set(name, val);
    }
    this->memory[name] = val;
}

SParameter Parameter::next() const {
    return this->_next;
}

int Parameter::position() const {
    return this->_position;
}

} // namespace spiral