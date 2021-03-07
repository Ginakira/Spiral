//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_HANDLER_H
#define SPIRAL_SPIRAL_HANDLER_H

namespace spiral {

class ASTree;

class PrintFactory;

class ExprFactory;

class BlockFactory;

class ConditionFactory;

class FactoryHandler {
public:
    static void init_factory(ASTree &);

    static FactoryHandler *get();

    virtual bool is_valid(ASTree &) = 0;

    virtual void handle(ASTree &) = 0;

protected:
    static FactoryHandler *head;

    FactoryHandler *next = nullptr;
};

class PrintFactoryHandler : public FactoryHandler {
public:
    bool is_valid(ASTree &) override;

    void handle(ASTree &) override;

private:
    static PrintFactory *factory;
};

class ExprFactoryHandler : public FactoryHandler {
public:
    bool is_valid(ASTree &) override;

    void handle(ASTree &) override;

private:
    static ExprFactory *factory;
};

class BlockFactoryHandler : public FactoryHandler {
public:
    bool is_valid(ASTree &) override;

    void handle(ASTree &) override;

private:
    static BlockFactory *factory;
};

class ConditionFactoryHandler : public FactoryHandler {
public:
    bool is_valid(ASTree &) override;

    void handle(ASTree &) override;

private:
    static ConditionFactory *factory;
};


} // namespace spiral

#endif //SPIRAL_SPIRAL_HANDLER_H
