//
// Created by Sakata on 2021/2/25.
//

#ifndef SPIRAL_PROGRAM_MASTER_H
#define SPIRAL_PROGRAM_MASTER_H

#include "SpiralLexer.h"
#include "SpiralParser.h"
#include <stdexcept>
#include <string>
#include <map>
#include <cstdio>

using std::string;
using std::map;
using std::runtime_error;
using std::printf;

class MasterChain;

class Parameters;

class IMaster;

class ProgramMaster;

class IFMaster;

class ExprMaster;

class IFactory {
public:
    virtual int valid(pANTLR3_BASE_TREE) = 0;

    virtual IMaster *creator(Parameters *) = 0;

    IFactory *next;

    virtual ~IFactory() = default;
};

class MasterChain {
public:
    static MasterChain *get() {
        if (MasterChain::single) return MasterChain::single;
        MasterChain::single = new MasterChain();
        return MasterChain::single;
    }

    static void destroy() {
        if (MasterChain::single == nullptr) return;
        MasterChain::get()->~MasterChain();
        MasterChain::single = nullptr;
    }

    int valid(pANTLR3_BASE_TREE, Parameters *);

private:
    static MasterChain *single;

    MasterChain();

    ~MasterChain();

    IFactory *p;
};

class Parameters {
public:
    explicit Parameters(Parameters *next) : next(next) {}

    int getVal(const string &);

    int setVal(const string &, int);

    int addVar(const string &);

    Parameters *next;
private:
    map<string, int> memory;
};

class IMaster {
public:
    explicit IMaster(Parameters *param) : param(param) {}

    virtual ~IMaster() = default;

    virtual int run(pANTLR3_BASE_TREE) = 0;

protected:
    Parameters *param;
};

class ProgramMaster : public IMaster {
public:
    class IProgramFactory : public IFactory {
    public:
        int valid(pANTLR3_BASE_TREE) override;

        IMaster *creator(Parameters *) override;
    };

    ProgramMaster() : IMaster(nullptr) {}

    explicit ProgramMaster(Parameters *param) : IMaster(param) {}

    int run(pANTLR3_BASE_TREE) override;

};

class IFMaster : public IMaster {
public:
    class IIFFactory : public IFactory {
    public:
        int valid(pANTLR3_BASE_TREE) override;

        IMaster *creator(Parameters *) override;
    };

    IFMaster() : IMaster(nullptr) {};

    explicit IFMaster(Parameters *param) : IMaster(param) {}

    int run(pANTLR3_BASE_TREE) override;
};

class ExprMaster : public IMaster {
public:
    class IExprFactory : public IFactory {
    public:
        int valid(pANTLR3_BASE_TREE) override;

        IMaster *creator(Parameters *) override;
    };

    ExprMaster() : IMaster(nullptr) {};

    explicit ExprMaster(Parameters *param) : IMaster(param) {}

    int run(pANTLR3_BASE_TREE) override;
};

class PrintMaster : public IMaster {
public:
    class IPrintFactory : public IFactory {
    public:
        int valid(pANTLR3_BASE_TREE) override;

        IMaster *creator(Parameters *) override;
    };

    PrintMaster() : IMaster(nullptr) {};

    explicit PrintMaster(Parameters *param) : IMaster(param) {}

    int run(pANTLR3_BASE_TREE) override;
};

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);

const char *getText(pANTLR3_BASE_TREE tree);

#endif //SPIRAL_PROGRAM_MASTER_H
