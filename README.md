# Spiral

An awesome interpreted language based on CPP & Antlr3.

## Build

```shell
cmake -S . -B build
```

## Run

```shell
cd bin
./spiral input.spr
# the "input.spr" can be any file you want to run with Spiral interpreter
```

## Supported features

- Define variable `def`
- Selective structure `if` `else`
- Loop structure `while` `do while` `for`
- Print statement `print`
- Scoping capabilities

## Design

- Extended Backus-Naur Form (EBNF)
- Responsibility chain
- Abstract factory
- Singleton

## Third-party libraries

- Antlr 3.4