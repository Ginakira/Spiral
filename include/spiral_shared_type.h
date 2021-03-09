//
// Created by Sakata on 2021/3/9.
//

#ifndef SPIRAL_SPIRAL_SHARED_TYPE_H
#define SPIRAL_SPIRAL_SHARED_TYPE_H

#include <memory>

namespace spiral {

class ASTree;

class Parameter;

class IValue;

class IntValue;

class FloatValue;

class StringValue;

using SIValue = std::shared_ptr<IValue>;
using SIntValue = std::shared_ptr<IntValue>;
using SFloatValue = std::shared_ptr<FloatValue>;
using SStringValue = std::shared_ptr<StringValue>;

} // namespace spiral


#endif //SPIRAL_SPIRAL_SHARED_TYPE_H