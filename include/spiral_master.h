//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_MASTER_H
#define SPIRAL_SPIRAL_MASTER_H

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

    virtual IValue *run() = 0;

    virtual ~IMaster() = default;

protected:
    ASTree &tree;
    Parameter *p;
};

class PrintMaster : public IMaster {
public:
    PrintMaster(ASTree &, Parameter *);

    IValue *run() override;
};

class ExprMaster : public IMaster {
public:
    ExprMaster(ASTree &, Parameter *);

    IValue *run() override;
};

class BlockMaster : public IMaster {
public:
    BlockMaster(ASTree &, Parameter *);

    IValue *run() override;
};

class ConditionMaster : public IMaster {
public:
    ConditionMaster(ASTree &, Parameter *);

    IValue *run() override;
};

} // namespace spiral


#endif //SPIRAL_SPIRAL_MASTER_H
