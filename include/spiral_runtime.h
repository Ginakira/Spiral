//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_RUNTIME_H
#define SPIRAL_SPIRAL_RUNTIME_H

#include "spiral_shared_type.h"

namespace spiral {

class ASTree;

class IValue;

class Parameter;

class RuntimeEnv {
public:
    explicit RuntimeEnv(ASTree &);

    void run();

    static SIValue getValue(ASTree &, SParameter);

private:
    ASTree &tree;
};

} // namespace spiral


#endif //SPIRAL_SPIRAL_RUNTIME_H
