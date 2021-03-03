//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_RUNTIME_H
#define SPIRAL_SPIRAL_RUNTIME_H

namespace spiral {

class ASTree;

class IValue;

class Parameter;

class RuntimeEnv {
public:
    explicit RuntimeEnv(ASTree &);

    void run();

    static IValue *getValue(ASTree &, Parameter *);

private:
    ASTree &tree;
};

} // namespace spiral


#endif //SPIRAL_SPIRAL_RUNTIME_H