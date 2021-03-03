//
// Created by Sakata on 2021/3/1.
//

#include "spiral_visitor.h"

namespace spiral {

void ConvertToStringVisitor::visit(spiral::IntValue *obj) {
    this->_result = std::to_string(obj->val());
}

void ConvertToStringVisitor::visit(spiral::FloatValue *obj) {
    this->_result = std::to_string(obj->val());
}

void ConvertToStringVisitor::visit(spiral::StringValue *obj) {
    this->_result = obj->val();
}

std::string ConvertToStringVisitor::result() const {
    return this->_result;
}

// Int Operator
IntValueOperator::IntValueOperator(IntValue *left, op_type op) : left(left), op(op) {}

void IntValueOperator::visit(IntValue *obj) { (this->left->*op)(*obj); }

void IntValueOperator::visit(FloatValue *obj) { (this->left->*op)(*obj); }

void IntValueOperator::visit(StringValue *obj) { (this->left->*op)(*obj); }

// Int plus
IntValuePlusOperatorVisitor::IntValuePlusOperatorVisitor(IntValue *left)
        : IntValueOperator(left, &IValue::operator+) {}

void IntValuePlusOperatorVisitor::visit(IntValue *obj) {
    this->_result = new IntValue(this->left->val() + obj->val());
}

void IntValuePlusOperatorVisitor::visit(FloatValue *obj) {
    this->_result = new FloatValue(this->left->val() + obj->val());
}

IValue *IntValuePlusOperatorVisitor::result() const {
    return this->_result;
}

// Int Minus
IntValueMinusOperatorVisitor::IntValueMinusOperatorVisitor(IntValue *left)
        : IntValueOperator(left, &IValue::operator-) {}

void IntValueMinusOperatorVisitor::visit(IntValue *obj) {
    this->_result = new IntValue(this->left->val() - obj->val());
}

void IntValueMinusOperatorVisitor::visit(FloatValue *obj) {
    this->_result = new FloatValue(this->left->val() - obj->val());
}

IValue *IntValueMinusOperatorVisitor::result() const {
    return this->_result;
}

// Int Times
IntValueTimesOperatorVisitor::IntValueTimesOperatorVisitor(IntValue *left)
        : IntValueOperator(left, &IValue::operator*) {}

void IntValueTimesOperatorVisitor::visit(IntValue *obj) {
    this->_result = new IntValue(this->left->val() * obj->val());
}

void IntValueTimesOperatorVisitor::visit(FloatValue *obj) {
    this->_result = new FloatValue(this->left->val() * obj->val());
}

IValue *IntValueTimesOperatorVisitor::result() const {
    return this->_result;
}


} // namespace spiral