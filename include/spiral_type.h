//
// Created by Sakata on 2021/2/27.
//

#ifndef SPIRAL_SPIRAL_TYPE_H
#define SPIRAL_SPIRAL_TYPE_H

#include <string>

#include "spiral_shared_type.h"

namespace spiral {

class IValue {
public:
    explicit IValue(std::string);

    class IVisitor {
    public:
        virtual void visit(IntValue *) = 0;

        virtual void visit(FloatValue *) = 0;

        virtual void visit(StringValue *) = 0;
    };

    std::string type();

    virtual void accept(IVisitor *) = 0;

    virtual bool isTrue() = 0;

    virtual bool isFalse();

    virtual SIValue operator+(IValue &);

    virtual SIValue operator-(IValue &);

    virtual SIValue operator*(IValue &);

    virtual SIValue operator/(IValue &);

    virtual SIValue operator%(IValue &);

    virtual bool operator<(IValue &) = 0;

    virtual bool operator>(IValue &);

    virtual bool operator<=(IValue &);

    virtual bool operator>=(IValue &);

    virtual bool operator==(IValue &);

    virtual bool operator!=(IValue &);


    void operator_plus_error(IValue &);

    void operator_minus_error(IValue &);

    void operator_times_error(IValue &);

    void operator_div_error(IValue &);

    void operator_mod_error(IValue &);

    void operator_compare_error(IValue &);

    virtual ~IValue() = default;

private:
    std::string type_name;
};

class IntValue : public IValue {
public:
    explicit IntValue(int = 0);

    void accept(IValue::IVisitor *) override;

    int val() const;

    bool isTrue() override;

    SIValue operator+(IValue &) override;

    SIValue operator-(IValue &) override;

    SIValue operator*(IValue &) override;

    SIValue operator/(IValue &) override;

    SIValue operator%(IValue &) override;

    bool operator<(IValue &) override;

    ~IntValue() override;

private:
    int _val;
};

class FloatValue : public IValue {
public:
    explicit FloatValue(double = 0.0);

    void accept(IValue::IVisitor *) override;

    double val() const;

    bool isTrue() override;

    SIValue operator+(IValue &) override;

    SIValue operator-(IValue &) override;

    SIValue operator*(IValue &) override;

    SIValue operator/(IValue &) override;

    bool operator<(IValue &) override;

    ~FloatValue() override;

private:
    double _val;
};

class StringValue : public IValue {
public:
    explicit StringValue(std::string = "");

    void accept(IValue::IVisitor *) override;

    std::string val() const;

    bool isTrue() override;

    SIValue operator+(IValue &) override;

    SIValue operator*(IValue &) override;

    bool operator<(IValue &) override;

    ~StringValue() override;

private:
    std::string _val;
};

static SIntValue null_val = std::make_shared<IntValue>(0);
static SIntValue true_val = std::make_shared<IntValue>(1);
static SIntValue false_val = std::make_shared<IntValue>(0);

} // namespace spiral

#endif //SPIRAL_SPIRAL_TYPE_H
