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

class ValueOperator : public IValue::IVisitor {
public:
    typedef void (IValue::*op_type)(IValue &);

    ValueOperator(IValue *, op_type);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    void visit(StringValue *) override;

protected:
    op_type op;
    IValue *lvalue;
    SIValue _result;
};

class IntValueOperator : public ValueOperator {
public:
    IntValueOperator(IntValue *, op_type);

    IntValue *left;
};

class FloatValueOperator : public ValueOperator {
public:
    FloatValueOperator(FloatValue *, op_type);

    FloatValue *left;
};

class StringValueOperator : public ValueOperator {
public:
    StringValueOperator(StringValue *, op_type);

    StringValue *left;
};


class IntValuePlusOperatorVisitor : public IntValueOperator {
public:
    explicit IntValuePlusOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};

class IntValueMinusOperatorVisitor : public IntValueOperator {
public:
    explicit IntValueMinusOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};

class IntValueTimesOperatorVisitor : public IntValueOperator {
public:
    explicit IntValueTimesOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};

class IntValueLittleOperatorVisitor : public IntValueOperator {
public:
    explicit IntValueLittleOperatorVisitor(IntValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};

class FloatValuePlusOperatorVisitor : public FloatValueOperator {
public:
    explicit FloatValuePlusOperatorVisitor(FloatValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};


class FloatValueMinusOperatorVisitor : public FloatValueOperator {
public:
    explicit FloatValueMinusOperatorVisitor(FloatValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};

class FloatValueTimesOperatorVisitor : public FloatValueOperator {
public:
    explicit FloatValueTimesOperatorVisitor(FloatValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};

class FloatValueLittleOperatorVisitor : public FloatValueOperator {
public:
    explicit FloatValueLittleOperatorVisitor(FloatValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    SIValue result() const;
};


class StringValuePlusOperatorVisitor : public StringValueOperator {
public:
    explicit StringValuePlusOperatorVisitor(StringValue *left);

    void visit(IntValue *) override;

    void visit(FloatValue *) override;

    void visit(StringValue *) override;

    SIValue result() const;
};

class StringValueTimesOperatorVisitor : public StringValueOperator {
public:
    explicit StringValueTimesOperatorVisitor(StringValue *left);

    void visit(IntValue *) override;

    SIValue result() const;
};

class StringValueLittleOperatorVisitor : public StringValueOperator {
public:
    explicit StringValueLittleOperatorVisitor(StringValue *left);

    void visit(StringValue *) override;

    SIValue result() const;
};


} // namespace spiral

#endif //SPIRAL_SPIRAL_VISITOR_H
