//
// Created by Sakata on 2021/2/27.
//

#ifndef SPIRAL_SPIRAL_TYPE_H
#define SPIRAL_SPIRAL_TYPE_H

#include <string>

namespace spiral {

class IntValue;

class FloatValue;

class StringValue;

class IValue {
public:
    explicit IValue(std::string);
    class IVisitor {
    public:
        virtual void visit(IntValue *) = 0;

        virtual void visit(FloatValue *) = 0;

        virtual void visit(StringValue *) = 0;
    };

    virtual void accept(IVisitor *) = 0;

    virtual IValue *operator+(IValue &);

    virtual IValue *operator-(IValue &);

    virtual IValue *operator*(IValue &);

    virtual ~IValue() = default;

private:
    std::string type_name;
};

class IntValue : public IValue {
public:
    explicit IntValue(int = 0);

    void accept(IValue::IVisitor *) override;

    int val() const;

    IValue *operator+(IValue &) override;

    IValue *operator-(IValue &) override;

    IValue *operator*(IValue &) override;

private:
    int _val;
};

class FloatValue : public IValue {
public:
    explicit FloatValue(double = 0.0);

    void accept(IValue::IVisitor *) override;

    double val() const;

//    IValue *operator+(IValue &) override;
//
//    IValue *operator-(IValue &) override;
//
//    IValue *operator*(IValue &) override;

private:
    double _val;
};

class StringValue : public IValue {
public:
    explicit StringValue(std::string = "");

    void accept(IValue::IVisitor *) override;

    std::string val() const;

//    IValue *operator+(IValue &) override;
//
//    IValue *operator*(IValue &) override;

private:
    std::string _val;
};

static IntValue *null_val = new IntValue(0);

} // namespace spiral

#endif //SPIRAL_SPIRAL_TYPE_H
