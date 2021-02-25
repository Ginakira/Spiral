//
// Created by Sakata on 2021/2/21.
//
#include <cassert>
#include <map>
#include <iostream>

#include "SpiralLexer.h"
#include "SpiralParser.h"
#include "program_master.h"

using std::map;
using std::string;
using std::cout;

class ExprTreeEvaluator {
    map<string, int> memory;
public:
    explicit ExprTreeEvaluator(ExprTreeEvaluator *);

    int &find(const string &);

    int run(pANTLR3_BASE_TREE);

    ExprTreeEvaluator *next;
};



int main(int argc, char *argv[]) {
    pANTLR3_INPUT_STREAM input;
    pSpiralLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    pSpiralParser parser;

    assert(argc > 1);
    input = antlr3FileStreamNew((pANTLR3_UINT8) argv[1], ANTLR3_ENC_8BIT);
    lex = SpiralLexerNew(input);

    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));

    parser = SpiralParserNew(tokens);
    SpiralParser_prog_return r = parser->prog(parser);
    pANTLR3_BASE_TREE tree = r.tree;

    ProgramMaster eval;
    eval.run(tree);

    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);

    return 0;
}

int ExprTreeEvaluator::run(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);

    if (tok) {
        switch (tok->type) {
            case BLOCK: {
                ExprTreeEvaluator new_block(this);
                int k = tree->getChildCount(tree);
                int r = 0;
                for (int i = 0; i < k; ++i) {
                    r = new_block.run(getChild(tree, i));
                }
                return r;
            }
            case DEF: {
                int k = tree->getChildCount(tree);
                for (int i = 0; i < k; ++i) {
                    pANTLR3_BASE_TREE child = getChild(tree, i);
                    string var(getText(child));
                    if (this->memory.find(var) != this->memory.end()) {
                        printf("Redefined variable: %s\n", var.c_str());
                        exit(-1);
                    }
                    this->memory[var] = 0;
                    if (child->getChildCount(child)) {
                        int r = this->run(getChild(child, 0));
                        this->memory[var] = r;
                    }
                }
                return 0;
            }
            case PRINT: {
                int r = run(getChild(tree, 0));
                printf("%d\n", r);
                return r;
            }
            case INT: {
                const char *s = getText(tree);
                if (s[0] == '~') {
                    return -atoi(s + 1);
                } else {
                    return atoi(s);
                }
            }
            case ID: {
                string var(getText(tree));
                return this->find(var);
            }
            case PLUS:
                return run(getChild(tree, 0)) + run(getChild(tree, 1));
            case MINUS:
                return run(getChild(tree, 0)) - run(getChild(tree, 1));
            case TIMES:
                return run(getChild(tree, 0)) * run(getChild(tree, 1));
            case DIV:
                return run(getChild(tree, 0)) / run(getChild(tree, 1));
            case ASSIGN: {
                string var(getText(getChild(tree, 0)));
                int &var_instance = this->find(var);
                int val = run(getChild(tree, 1));
                var_instance = val;
                return val;
            }
            default: {
                printf("Unhandled token: #%d\n", tok->type);
                return -1;
            }
        }
    } else {
        int k = tree->getChildCount(tree);
        int r = 0;
        for (int i = 0; i < k; ++i) {
            r = run(getChild(tree, i));
            printf("value: %d\n", r);
        }
        return r;
    }
}

int &ExprTreeEvaluator::find(const string &var) {
    if (this->memory.find(var) != this->memory.end()) {
        return this->memory[var];
    }
    if (this->next) return this->next->find(var);
    printf("Undefined variable: %s\n", var.c_str());
    exit(-1);
}

ExprTreeEvaluator::ExprTreeEvaluator(ExprTreeEvaluator *_next) : next(_next) {

}