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

    DFA *build(ASTree *);

    static std::stack<IDFANode *> breakPoint;

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


protected:
    IDFANode *_first{};
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

private:
    int position;
};

class BlockEndDFANode : public SingleDFANode {
public:
    explicit BlockEndDFANode(int);

    IDFANode *next(SParameter &) override;

private:
    int position;
};

class ConditionDFANode : public MultiDFANode {
public:
    explicit ConditionDFANode(ASTree *);

    IDFANode *next(SParameter &) override;
};

class BreakDFANode : public SingleDFANode {
public:
    explicit BreakDFANode(IDFANode *node);

    IDFANode *next(SParameter &) override;

private:
    IDFANode *jump_node;
};

class BlankDFANode : public SingleDFANode {
public:
    BlankDFANode();

    IDFANode *next(SParameter &) override;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_DFA_H
