//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_MASTER_H
#define SPIRAL_SPIRAL_MASTER_H

#include "spiral_shared_type.h"

namespace spiral {

class ASTree;

class IValue;

class Parameter;

class IMaster {
public:
    IMaster(ASTree *, SParameter);

    class IFactory {
    public:
        virtual IMaster *create(ASTree *, SParameter) = 0;

        virtual void destroy(IMaster *);
    };

    virtual SIValue run() = 0;

    virtual ~IMaster() = default;

protected:
    ASTree *tree;
    SParameter p;
};

class PrintMaster : public IMaster {
public:
    PrintMaster(ASTree *, SParameter);

    SIValue run() override;
};

class ExprMaster : public IMaster {
public:
    ExprMaster(ASTree *, SParameter);

    SIValue run() override;
};

class BlockMaster : public IMaster {
public:
    BlockMaster(ASTree *, SParameter);

    SIValue run() override;
};

class ConditionMaster : public IMaster {
public:
    ConditionMaster(ASTree *, SParameter);

    SIValue run() override;
};


class ControlMaster : public IMaster {
public:
    ControlMaster(ASTree *, SParameter);

    SIValue run() override;
};
} // namespace spiral


#endif //SPIRAL_SPIRAL_MASTER_H
