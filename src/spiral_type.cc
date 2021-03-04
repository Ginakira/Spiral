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


std::string IValue::type() {
    return this->type_name;
}

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
IValue * IValue::operator+(IValue &obj) {
    this->operator_plus_error(obj);
    return spiral::null_val;
}

IValue * IValue::operator-(IValue &obj) {
    this->operator_minus_error(obj);
    return spiral::null_val;
}

IValue * IValue::operator*(IValue &obj) {
    this->operator_times_error(obj);
    return spiral::null_val;
}

void IValue::operator_plus_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type_name + " + " + obj.type_name + ")");
}

void IValue::operator_minus_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type_name + " - " + obj.type_name + ")");
}

void IValue::operator_times_error(IValue &obj) {
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

// Float operator
IValue *FloatValue::operator+(IValue &obj) {
    FloatValuePlusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

IValue *FloatValue::operator-(IValue &obj) {
    FloatValueMinusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

IValue *FloatValue::operator*(IValue &obj) {
    FloatValueTimesOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

// String operator
IValue *StringValue::operator+(IValue &obj) {
    StringValuePlusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

IValue *StringValue::operator*(IValue &obj) {
    StringValueTimesOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

} // namespace spiral;