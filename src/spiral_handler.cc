//
// Created by Sakata on 2021/3/1.
//

#include <string>

#include "SpiralLexer.h"
#include "spiral_handler.h"
#include "spiral_tree.h"
#include "spiral_factory.h"

namespace spiral {

void FactoryHandler::init_factory(ASTree &tree) {
    FactoryHandler *p = FactoryHandler::get();
    for (; p != nullptr; p = p->next) {
        if (!p->is_valid(tree)) continue;
        p->handle(tree);
        break;
    }
    if (p == nullptr) {
        throw std::runtime_error(
                "There is no appropriate handler in FactoryHandler::init_factory(). Token type: " +
                std::to_string(tree.type()));
    }
    for (int i = 0; i < tree.size(); ++i) {
        FactoryHandler::init_factory(tree.at(i));
    }
}

FactoryHandler *FactoryHandler::get() {
    if (FactoryHandler::head == nullptr) {
        head = new PrintFactoryHandler();
        head->next = new ExprFactoryHandler();
        head->next->next = new BlockFactoryHandler();
        head->next->next->next = new ConditionFactoryHandler();
    }
    return head;
}

bool PrintFactoryHandler::is_valid(ASTree &tree) {
    switch (tree.type()) {
        case PRINT:
            return true;
        default:
            return false;
    }
}

void PrintFactoryHandler::handle(ASTree &tree) {
    tree.factory = PrintFactoryHandler::factory;
}

bool ExprFactoryHandler::is_valid(ASTree &tree) {
    switch (tree.type()) {
        case INT:
        case FLOAT:
        case STRING:
        case ID:
        case PLUS:
        case MINUS:
        case TIMES:
        case ASSIGN:
        case DEF:
            return true;
        default:
            return false;
    }
}

void ExprFactoryHandler::handle(ASTree &tree) {
    tree.factory = ExprFactoryHandler::factory;
}


bool BlockFactoryHandler::is_valid(ASTree &tree) {
    switch (tree.type()) {
        case BLOCK:
            return true;
        default:
            return false;
    }
}

void BlockFactoryHandler::handle(ASTree &tree) {
    tree.factory = BlockFactoryHandler::factory;
}

bool ConditionFactoryHandler::is_valid(ASTree &tree) {
    switch (tree.type()) {
        case OR:
        case AND:
        case EQ:
        case NE:
        case GT:
        case GE:
        case LITTLE:
        case LE:
            return true;
        default:
            return false;
    }
}

void ConditionFactoryHandler::handle(ASTree &tree) {
    tree.factory = ConditionFactoryHandler::factory;
}


PrintFactory *PrintFactoryHandler::factory = new PrintFactory();

ExprFactory *ExprFactoryHandler::factory = new ExprFactory();

BlockFactory *BlockFactoryHandler::factory = new BlockFactory();

ConditionFactory *ConditionFactoryHandler::factory = new ConditionFactory();

FactoryHandler *FactoryHandler::head = nullptr;

} // namespace spiral