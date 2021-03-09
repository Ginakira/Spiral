//
// Created by Sakata on 2021/2/28.
//

#ifndef SPIRAL_SPIRAL_PARAMETER_H
#define SPIRAL_SPIRAL_PARAMETER_H

#include <map>
#include <string>
#include "spiral_shared_type.h"

using std::map;
using std::string;

namespace spiral {

class Parameter {
public:
    explicit Parameter(Parameter *next = nullptr);

    void define_param(const string &);

    SIValue get(const string &) const;

    void set(const string &, const SIValue& );

    Parameter *next() const;

private:
    mutable map<string, SIValue> memory;
    Parameter *_next;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_PARAMETER_H
