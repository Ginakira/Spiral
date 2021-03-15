//
// Created by Sakata on 2021/3/12.
//

#include "spiral_runtime.h"
#include "spiral_parameter.h"
#include "spiral_tree.h"
#include "spiral_type.h"
#include "spiral_dfa.h"

#include <utility>

namespace spiral {

std::stack<IDFANode *> DFA::breakPoint;

DFA::DFA() : head(nullptr), tail(nullptr) {}

DFA::DFA(ASTree *tree) {
    DFA *ret = DFA::build(tree);
    this->head = ret->head;
    this->tail = ret->tail;
}

void DFA::run(SParameter &p) {
    IDFANode *current = this->head;
    while (current) {
//        printf("%s\n", current->type().c_str());
        current = current->next(p);
    }
}

DFA *DFA::build(ASTree *tree) {
    DFA *ret = new DFA();
    switch (tree->type()) {
        case BREAK: {
            ret->head = ret->tail = new BreakDFANode(breakPoint.top());
            break;
        }
        case IF: {
            DFA *temp;
            ret->head = new ConditionDFANode(tree->at(0));
            ret->tail = new BlankDFANode();
            temp = DFA::build(tree->at(1));
            ret->head->at(0) = temp->head;
            temp->tail->at(0) = ret->tail;
            if (tree->size() == 3) { // 存在else子句
                temp = DFA::build(tree->at(2));
                ret->head->at(1) = temp->head;
                temp->tail->at(0) = ret->tail;
            } else {
                ret->head->at(1) = ret->tail;
            }
            break;
        }
        case BLOCK: {
            ret->head = new BlockBeginDFANode();
            ret->tail = new BlockEndDFANode();
            DFA *temp;
            IDFANode *p = ret->head;
            for (int i = 0; i < tree->size(); ++i) {
                temp = DFA::build(tree->at(i));
                p->at(0) = temp->head;
                p = temp->tail;
            }
            p->at(0) = ret->tail;
            break;
        }
        case WHILE: {
            ret->head = new ConditionDFANode(tree->at(0));
            ret->tail = new BlankDFANode();
            breakPoint.push(ret->tail);
            DFA *temp = DFA::build(tree->at(1));
            ret->head->at(0) = temp->head;
            temp->tail->at(0) = ret->head;
            ret->head->at(1) = ret->tail;
            breakPoint.pop();
            break;
        }
        case DOWHILE: {
            DFA *temp = DFA::build(tree->at(1));
            ret->head = temp->head;
            ret->tail = new BlankDFANode();
            breakPoint.push(ret->tail);
            temp->tail->at(0) = new ConditionDFANode(tree->at(0));
            temp->tail->at(0)->at(0) = ret->head;
            temp->tail->at(0)->at(1) = ret->tail;
            breakPoint.pop();
            break;
        }
        case FOR: {
            ret->head = new BlockBeginDFANode();
            ret->tail = new BlockEndDFANode();
            breakPoint.push(ret->tail);
            IDFANode *init_node = new ExprDFANode(tree->at(0));
            IDFANode *condition_node = new ConditionDFANode(tree->at(1));
            IDFANode *do_node = new ExprDFANode(tree->at(2));
            DFA *stmt = DFA::build(tree->at(3));
            ret->head->at(0) = init_node;
            init_node->at(0) = condition_node;
            condition_node->at(0) = stmt->head;
            condition_node->at(1) = ret->tail;
            stmt->tail->at(0) = do_node;
            do_node->at(0) = condition_node;
            breakPoint.pop();
            break;
        }
        default: {
            ret->head = ret->tail = new ExprDFANode(tree);
            break;
        }
    }
    return ret;
}


// DFA Node constructor
IDFANode::IDFANode(ASTree *tree, int n, std::string _type) : tree(tree), children(n), _type(std::move(_type)){}

SingleDFANode::SingleDFANode(ASTree *tree, std::string _type) : IDFANode(tree, 1, std::move(_type)) {}

MultiDFANode::MultiDFANode(ASTree *tree, std::string _type) : IDFANode(tree, 2, std::move(_type)) {}

ExprDFANode::ExprDFANode(ASTree *tree) : SingleDFANode(tree, "ExprDFANode") {}

BlockBeginDFANode::BlockBeginDFANode() : SingleDFANode(nullptr, "BlockBeginDFANode") {}

BlockEndDFANode::BlockEndDFANode() : SingleDFANode(nullptr, "BlockEndDFANode") {}

ConditionDFANode::ConditionDFANode(ASTree *tree) : MultiDFANode(tree, "ConditionDFANode") {}

BreakDFANode::BreakDFANode(IDFANode *node) : SingleDFANode(nullptr, "BreakDFANode"), jump_node(node) {}

BlankDFANode::BlankDFANode() : SingleDFANode(nullptr, "BlankDFANode") {}


IDFANode *&IDFANode::at(int index) {
    return this->children[index];
}

std::string IDFANode::type() {
    return this->_type;
}

IDFANode *ExprDFANode::next(SParameter &p) {
    RuntimeEnv::getValue(this->tree, p);
    return this->at(0);
}

IDFANode *BlockBeginDFANode::next(SParameter &p) {
    p = std::make_shared<Parameter>(p);
    return this->at(0);
}

IDFANode *BlockEndDFANode::next(SParameter &p) {
    p = p->next();
    return this->at(0);
}

IDFANode *ConditionDFANode::next(SParameter &p) {
    SIValue val = RuntimeEnv::getValue(this->tree, p);
    return val->isTrue() ? this->at(0) : this->at(1);
}

IDFANode *BreakDFANode::next(SParameter &p) {
    return this->jump_node;
}

IDFANode *BlankDFANode::next(SParameter &p) {
    return this->at(0);
}

} // namespace spiral