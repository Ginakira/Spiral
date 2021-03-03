//
// Created by Sakata on 2021/2/28.
//

#include "spiral_tree.h"
#include <stdexcept>


namespace spiral {

ASTree::ASTree(pANTLR3_BASE_TREE tree) : tree(tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    _type = tok->type;
    _size = tree->getChildCount(tree);
    for (int i = 0; i < _size; ++i) {
        this->child.emplace_back(
                ASTree((pANTLR3_BASE_TREE) tree->getChild(tree, i))
        );
    }
}

int ASTree::type() const { return this->_type; }

int ASTree::size() const {
    return tree->getChildCount(tree);
}

ASTree &ASTree::at(int ind) {
    if (this->size() <= ind) {
        throw std::runtime_error("ASTree getChild() error occurred! An unexpected index of child.");
    }
    return this->child[ind];
}

std::string ASTree::text() const {
    return (const char *) tree->getText(tree)->chars;
}

} // namespace spiral