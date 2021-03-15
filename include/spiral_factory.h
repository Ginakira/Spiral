//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_FACTORY_H
#define SPIRAL_SPIRAL_FACTORY_H

#include "spiral_master.h"

namespace spiral {

class PrintFactory : public IMaster::IFactory {
    IMaster *create(ASTree *, SParameter) override;
};

class ExprFactory : public IMaster::IFactory {
    IMaster *create(ASTree *, SParameter) override;
};

class BlockFactory : public IMaster::IFactory {
    IMaster *create(ASTree *, SParameter) override;
};

class ConditionFactory : public IMaster::IFactory {
    IMaster *create(ASTree *, SParameter) override;
};

class ControlFactory : public IMaster::IFactory {
    IMaster *create(ASTree *, SParameter) override;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_FACTORY_H
