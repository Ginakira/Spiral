//
// Created by Sakata on 2021/2/27.
//

#include <utility>

#include "spiral_type.h"
#include "spiral_visitor.h"

namespace spiral {

// constructor
IValue::IValue(std::string t_name) : type_name(std::move(t_name)) {}

IntValue::IntValue(int x) : IValue("int"), _val(x) {}

FloatValue::FloatValue(double x) : IValue("float"), _val(x) {}

StringValue::StringValue(std::string x) : IValue("string"), _val(std::move(x)) {}


// visitor function
void IntValue::accept(IValue::IVisitor *vis) {
    vis->visit(this);
}

void FloatValue::accept(IValue::IVisitor *vis) {
    vis->visit(this);
}

void StringValue::accept(IValue::IVisitor *vis) {
    vis->visit(this);
}

// get value function
int IntValue::val() const {
    return this->_val;
}

double FloatValue::val() const {
    return this->_val;
}

std::string StringValue::val() const {
    return this->_val;
}

// Base operator (when no appropriate operator between types)
IValue *IValue::operator+(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type_name + " + " + obj.type_name + ")");
}

IValue *IValue::operator-(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type_name + " - " + obj.type_name + ")");
}

IValue *IValue::operator*(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type_name + " * " + obj.type_name + ")");
}

// Int operator
IValue *IntValue::operator+(IValue &obj) {
    IntValuePlusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

IValue *IntValue::operator-(IValue &obj) {
    IntValueMinusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

IValue *IntValue::operator*(IValue &obj) {
    IntValueTimesOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

} // namespace spiral;