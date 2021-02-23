//
// Created by Sakata on 2021/2/21.
//
#include <cassert>
#include <map>
#include <iostream>

#include "ExprCppTreeLexer.h"
#include "ExprCppTreeParser.h"

using std::map;
using std::string;
using std::cout;

class ExprTreeEvaluator {
    map<string, int> memory;
public:
    explicit ExprTreeEvaluator(ExprTreeEvaluator *);

    int find(const string &);

    int run(pANTLR3_BASE_TREE);

    ExprTreeEvaluator *next;
};

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);

const char *getText(pANTLR3_BASE_TREE tree);

int main(int argc, char *argv[]) {
    pANTLR3_INPUT_STREAM input;
    pExprCppTreeLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    pExprCppTreeParser parser;

    assert(argc > 1);
    input = antlr3FileStreamNew((pANTLR3_UINT8) argv[1], ANTLR3_ENC_8BIT);
    lex = ExprCppTreeLexerNew(input);

    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));

    parser = ExprCppTreeParserNew(tokens);

    ExprCppTreeParser_prog_return r = parser->prog(parser);

    pANTLR3_BASE_TREE tree = r.tree;

    ExprTreeEvaluator eval(nullptr);
    int rr = eval.run(tree);
    cout << "Evaluator result: " << rr << '\n';

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
                int val = run(getChild(tree, 1));
                memory[var] = val;
                return val;
            }
            default: {
                cout << "Unhandled token: #" << tok->type << '\n';
                return -1;
            }
        }
    } else {
        int k = tree->getChildCount(tree);
        int r = 0;
        for (int i = 0; i < k; ++i) {
            r = run(getChild(tree, i));
            cout << "value: " << r << '\n';
        }
        return r;
    }
}

int ExprTreeEvaluator::find(const string &var) {
    if (this->memory.find(var) != this->memory.end()) {
        return this->memory[var];
    }
    if (this->next) return this->next->find(var);
    return 0;
}

ExprTreeEvaluator::ExprTreeEvaluator(ExprTreeEvaluator *_next) : next(_next) {

}


pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE tree, unsigned i) {
    assert(i < tree->getChildCount(tree));
    return (pANTLR3_BASE_TREE) tree->getChild(tree, i);
}

const char *getText(pANTLR3_BASE_TREE tree) {
    return (const char *) tree->getText(tree)->chars;
}