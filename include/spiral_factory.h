//
// Created by Sakata on 2021/3/1.
//

#ifndef SPIRAL_SPIRAL_FACTORY_H
#define SPIRAL_SPIRAL_FACTORY_H

#include "spiral_master.h"

namespace spiral {

class PrintFactory : public IMaster::IFactory {
    IMaster *create(ASTree &, Parameter *) override;
};

class ExprFactory : public IMaster::IFactory {
    IMaster *create(ASTree &, Parameter *) override;
};

class BlockFactory : public IMaster::IFactory {
    IMaster *create(ASTree &, Parameter *) override;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_FACTORY_H
