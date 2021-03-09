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
    IMaster(ASTree &, Parameter *);

    class IFactory {
    public:
        virtual IMaster *create(ASTree &, Parameter *) = 0;

        virtual void destroy(IMaster *);
    };

    virtual SIValue run() = 0;

    virtual ~IMaster() = default;

protected:
    ASTree &tree;
    Parameter *p;
};

class PrintMaster : public IMaster {
public:
    PrintMaster(ASTree &, Parameter *);

    SIValue run() override;
};

class ExprMaster : public IMaster {
public:
    ExprMaster(ASTree &, Parameter *);

    SIValue run() override;
};

class BlockMaster : public IMaster {
public:
    BlockMaster(ASTree &, Parameter *);

    SIValue run() override;
};

class ConditionMaster : public IMaster {
public:
    ConditionMaster(ASTree &, Parameter *);

    SIValue run() override;
};


class ControlMaster : public IMaster {
public:
    ControlMaster(ASTree &, Parameter *);

    SIValue run() override;
};
} // namespace spiral


#endif //SPIRAL_SPIRAL_MASTER_H
