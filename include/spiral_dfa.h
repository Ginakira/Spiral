//
// Created by Sakata on 2021/3/12.
//

#ifndef SPIRAL_SPIRAL_DFA_H
#define SPIRAL_SPIRAL_DFA_H

#include <vector>
#include <stack>
#include <string>

#include "spiral_shared_type.h"

namespace spiral {

class DFA {
public:
    explicit DFA(ASTree *);

    void run(SParameter &);

private:
    DFA();

    static DFA *build(ASTree *);

    static std::stack<IDFANode *> breakPoint;
    static std::stack<IDFANode *> continuePoint;
    static std::stack<IDFANode *> returnPoint;
    static int blockPosition;
    IDFANode *head, *tail;
};

class IDFANode {
public:
    IDFANode(ASTree *, int, std::string);

    virtual IDFANode *next(SParameter &) = 0;

    IDFANode *&at(int);

    std::string type();

protected:
    ASTree *tree;
    std::vector<IDFANode *> children;
    std::string _type;
};

class SingleDFANode : public IDFANode {
public:
    explicit SingleDFANode(ASTree *, std::string);

    IDFANode *next(SParameter &) override = 0;
};

class MultiDFANode : public IDFANode {
public:
    explicit MultiDFANode(ASTree *, std::string);

    IDFANode *next(SParameter &) override = 0;
};

class ExprDFANode : public SingleDFANode {
public:
    explicit ExprDFANode(ASTree *);

    IDFANode *next(SParameter &) override;
};

class BlockBeginDFANode : public SingleDFANode {
public:
    explicit BlockBeginDFANode(int);

    IDFANode *next(SParameter &) override;

    int pos() const;

private:
    int _pos;
};

class BlockEndDFANode : public SingleDFANode {
public:
    explicit BlockEndDFANode(int);

    IDFANode *next(SParameter &) override;

    int pos() const;

private:
    int _pos;
};

class ConditionDFANode : public MultiDFANode {
public:
    explicit ConditionDFANode(ASTree *);

    IDFANode *next(SParameter &) override;
};

class JumpDFANode : public SingleDFANode {
public:
    explicit JumpDFANode(IDFANode *);

    IDFANode *next(SParameter &) override;

private:
    IDFANode *jump_node;
};

class BlankDFANode : public SingleDFANode {
public:
    explicit BlankDFANode(int = -100);

    void set_pos(int);

    int pos() const;

    IDFANode *next(SParameter &) override;

private:
    int _pos;
};

class DefineFunctionDFANode : public SingleDFANode {
public:
    DefineFunctionDFANode(ASTree *, DFA *);

    IDFANode *next(SParameter &) override;

private:
    SFunctionValue func;
};

class ReturnDFANode : public JumpDFANode {
public:
    ReturnDFANode(IDFANode *, ASTree *);

    IDFANode *next(SParameter &) override;

private:
    ASTree *tree;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_DFA_H
