//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_VISITOR_H
#define SPIRAL_SPIRAL_VISITOR_H

#include "spiral_type.h"

namespace spiral {

class ConvertToStringVisitor : public IValue::IVisitor {
public:
    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    void visit(StringValue *) override;

    std::string result() const;

private:
    std::string _result;
};

class IntValueOperator : public IValue::IVisitor {
public:
    typedef IValue *(IValue::*op_type)(IValue &);

    IntValueOperator(IntValue *, op_type);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    void visit(StringValue *) override;

    IntValue *left;

private:
    op_type op;

};

class IntValuePlusOperatorVisitor : public IntValueOperator {
public:
    explicit IntValuePlusOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    IValue *result() const;

private:
    IValue *_result{};
};

class IntValueMinusOperatorVisitor : public IntValueOperator {
public:
    explicit IntValueMinusOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    IValue *result() const;

private:
    IValue *_result{};
};

class IntValueTimesOperatorVisitor : public IntValueOperator {
public:
    explicit IntValueTimesOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    IValue *result() const;

private:
    IValue *_result{};
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_VISITOR_H
