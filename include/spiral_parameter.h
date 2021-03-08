//
// Created by Sakata on 2021/2/28.
//

#ifndef SPIRAL_SPIRAL_PARAMETER_H
#define SPIRAL_SPIRAL_PARAMETER_H

#include <map>
#include <string>

using std::map;
using std::string;

namespace spiral {

class IValue;

class Parameter {
public:
    explicit Parameter(Parameter *next = nullptr);

    void define_param(const string &);

    IValue *get(const string &) const;

    void *set(const string &, IValue *);

    Parameter *next() const;

private:
    mutable map<string, IValue *> memory;
    Parameter *_next;
};

} // namespace spiral

#endif //SPIRAL_SPIRAL_PARAMETER_H
