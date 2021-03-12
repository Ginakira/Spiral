//
// Created by Sakata on 2021/2/21.
//
#include <cassert>

#include "SpiralLexer.h"
#include "SpiralParser.h"

#include "spiral_master.h"
#include "spiral_tree.h"
#include "spiral_runtime.h"

pANTLR3_INPUT_STREAM input;
pSpiralLexer lex;
pANTLR3_COMMON_TOKEN_STREAM tokens;
pSpiralParser parser;

spiral::ASTree init(int argc, char *argv[]) {
    assert(argc > 1);
    input = antlr3FileStreamNew((pANTLR3_UINT8) argv[1], ANTLR3_ENC_8BIT);
    lex = SpiralLexerNew(input);

    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));

    parser = SpiralParserNew(tokens);
    SpiralParser_prog_return r = parser->prog(parser);
    return spiral::ASTree(r.tree);
}

void destroy() {
    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);
}

void check(spiral::ASTree &tree) {
    printf("%s %d\n", tree.text().c_str(), tree.type());
    for (int i = 0; i < tree.size(); ++i) {
        check(tree.at(i));
    }
}

int main(int argc, char *argv[]) {
    spiral::ASTree tree = init(argc, argv);
    spiral::RuntimeEnv env(tree);
    env.run();
    destroy();
    return 0;
}