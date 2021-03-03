//
// Created by Sakata on 2021/2/28.
//

#ifndef SPIRAL_SPIRAL_TREE_H
#define SPIRAL_SPIRAL_TREE_H

#include <string>
#include <vector>

#include "SpiralLexer.h"
#include "SpiralParser.h"
#include "spiral_master.h"

namespace spiral {

class ASTree {
public:
    explicit ASTree(pANTLR3_BASE_TREE tree);

    int size() const;

    ASTree &at(int ind);

    std::string text() const;

    int type() const;

    IMaster::IFactory *factory;

private:
    pANTLR3_BASE_TREE tree;
    int _type;
    int _size;
    std::vector<ASTree> child;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_TREE_H
