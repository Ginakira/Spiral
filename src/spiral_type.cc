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

bool IValue::isFalse() {
    return !(this->isTrue());
}

// Base operator (when no appropriate operator between types)
IValue *IValue::operator+(IValue &obj) {
    this->operator_plus_error(obj);
    return spiral::null_val;
}

IValue *IValue::operator-(IValue &obj) {
    this->operator_minus_error(obj);
    return spiral::null_val;
}

IValue *IValue::operator*(IValue &obj) {
    this->operator_times_error(obj);
    return spiral::null_val;
}

bool IValue::operator>(IValue &obj) {
    return obj < (*this);
}

bool IValue::operator<=(IValue &obj) {
    return !(obj < (*this));
}

bool IValue::operator>=(IValue &obj) {
    return !((*this) < obj);
}

bool IValue::operator==(IValue &obj) {
    return !((*this) < obj) && !(obj < (*this));
}

bool IValue::operator!=(IValue &obj) {
    return (*this) < obj || obj < (*this);
}


void IValue::operator_plus_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type() + " + " + obj.type() + ")");
}

void IValue::operator_minus_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type() + " - " + obj.type() + ")");
}

void IValue::operator_times_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type() + " * " + obj.type() + ")");
}

void IValue::operator_compare_error(IValue &obj) {
    throw std::runtime_error("Comparisons between " + this->type() + " and " + obj.type() + " are not supported!");
}


// Int operator
bool IntValue::isTrue() {
    return this->_val != 0;
}

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

bool IntValue::operator<(IValue &obj) {
    IntValueLittleOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result()->isTrue();
}

// Float operator
bool FloatValue::isTrue() {
    return this->_val != 0.0;
}

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

bool FloatValue::operator<(IValue &obj) {
    FloatValueLittleOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result()->isTrue();
}

// String operator
bool StringValue::isTrue() {
    return !(this->_val.empty());
}

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

bool StringValue::operator<(IValue &obj) {
    StringValueLittleOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result()->isTrue();
}

} // namespace spiral;