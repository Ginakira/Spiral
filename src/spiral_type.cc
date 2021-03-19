//
// Created by Sakata on 2021/2/27.
//

#include <sstream>

#include "spiral_type.h"
#include "spiral_visitor.h"
#include "spiral_dfa.h"
#include "spiral_runtime.h"
#include "spiral_parameter.h"
#include "spiral_tree.h"

namespace spiral {

// constructor
IValue::IValue(std::string t_name) : type_name(std::move(t_name)) {}

IntValue::IntValue(int x) : IValue("int"), _val(x) {}

FloatValue::FloatValue(double x) : IValue("float"), _val(x) {}

StringValue::StringValue(std::string x) : IValue("string"), _val(std::move(x)) {}

FunctionValue::FunctionValue(ASTree *tree, DFA *dfa)
        : IValue("function"), _val(dfa) { this->convert(tree); }

// destructor
IntValue::~IntValue() {
//    printf("destructor : %d\n", val());
}

FloatValue::~FloatValue() {
//    printf("destructor : %lf\n", val());
}

StringValue::~StringValue() {
//    printf("destructor : %s\n", val().c_str());
}

FunctionValue::~FunctionValue() {
//    printf("destructor : %s\n", val().c_str());
}

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

void FunctionValue::accept(IValue::IVisitor *vis) {
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

SIValue IValue::run(SParameter &p, __unused ASTree *tree) {
    throw std::runtime_error(this->type() + " is not callable!");
}

// Base operator (when no appropriate operator between types)
SIValue IValue::operator+(IValue &obj) {
    this->operator_plus_error(obj);
    return spiral::null_val;
}

SIValue IValue::operator-(IValue &obj) {
    this->operator_minus_error(obj);
    return spiral::null_val;
}

SIValue IValue::operator*(IValue &obj) {
    this->operator_times_error(obj);
    return spiral::null_val;
}

SIValue IValue::operator/(IValue &obj) {
    this->operator_div_error(obj);
    return spiral::null_val;
}

SIValue IValue::operator%(IValue &obj) {
    this->operator_mod_error(obj);
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

bool IValue::operator<(IValue &obj) {
    this->operator_compare_error(obj);
    return false;
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

void IValue::operator_div_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type() + " / " + obj.type() + ")");
}

void IValue::operator_mod_error(IValue &obj) {
    throw std::runtime_error("Unsupported operator :(" + this->type() + " % " + obj.type() + ")");
}

void IValue::operator_compare_error(IValue &obj) {
    throw std::runtime_error("Comparisons between " + this->type() + " and " + obj.type() + " are not supported!");
}


// Int operator
bool IntValue::isTrue() {
    return this->_val != 0;
}

SIValue IntValue::operator+(IValue &obj) {
    IntValuePlusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue IntValue::operator-(IValue &obj) {
    IntValueMinusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue IntValue::operator*(IValue &obj) {
    IntValueTimesOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue IntValue::operator/(IValue &obj) {
    IntValueDivOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue IntValue::operator%(IValue &obj) {
    IntValueModOperatorVisitor vis(this);
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

SIValue FloatValue::operator+(IValue &obj) {
    FloatValuePlusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue FloatValue::operator-(IValue &obj) {
    FloatValueMinusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue FloatValue::operator*(IValue &obj) {
    FloatValueTimesOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue FloatValue::operator/(IValue &obj) {
    FloatValueDivOperatorVisitor vis(this);
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

SIValue StringValue::operator+(IValue &obj) {
    StringValuePlusOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

SIValue StringValue::operator*(IValue &obj) {
    StringValueTimesOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result();
}

bool StringValue::operator<(IValue &obj) {
    StringValueLittleOperatorVisitor vis(this);
    obj.accept(&vis);
    return vis.result()->isTrue();
}


// FunctionValue operator
bool FunctionValue::isTrue() {
    return true;
}

void FunctionValue::convert(ASTree *tree) {
    this->func_name = tree->at(0)->text();
    this->params.clear();
    for (int i = 0, n = tree->at(1)->size(); i < n; ++i) {
        this->params.emplace_back(tree->at(1)->at(i)->text());
    }
}

std::string FunctionValue::val() const {
    std::string ret = "function " + this->func_name + "(";
    for (int i = 0; i < this->params.size(); ++i) {
        if (i) ret += ", ";
        ret += this->params[i];
    }
    ret += ");";
    return ret;
}

std::string FunctionValue::name() const {
    return this->func_name;
}

void FunctionValue::set_init_param(SParameter init_p) {
    this->init_param = std::move(init_p);
}

SIValue FunctionValue::run(SParameter &p, ASTree *param) {
    this->init_param = std::make_shared<Parameter>(this->init_param);
    if (param->size() != this->params.size()) {
        std::string msg;
        std::stringstream out(msg);
        out << "Incorrect call to function " << this->name() << "!\n";
        out << "\texpect " << this->params.size() << " params, but ";
        out << param->size() << " given.\n";
        throw std::runtime_error(msg);
    }
    for (int i = 0; i < this->params.size(); ++i) {
        this->init_param->define_param(this->params[i]);
        this->init_param->set(this->params[i], RuntimeEnv::getValue(param->at(i), p->next()));
    }
    this->init_param->define_param(spiral::ReturnValueName);
    this->init_param->set(spiral::ReturnValueName, spiral::null_val);
    this->_val->run(this->init_param);
    SIValue retValue = this->init_param->get(spiral::ReturnValueName);
    this->init_param = this->init_param->next();
    return retValue;
}

} // namespace spiral;