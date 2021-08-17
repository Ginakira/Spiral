# Spiral

Spiral 是一个基于 Antlr3 / C++ 实现的自制语言及简易解释器。

Spiral 的语法风格参考了 C 与 Python，在吸收了 C 语言优雅易读的语法风格的同时，引入了 Python 的弱类型系统，提升编码效率。

## 构建

```shell
cmake -S . -B build
cd build
cmake --build .
```

构建好的解释器将会生成在 `bin` 文件夹内。

## 运行

将编译好的解释器加入系统环境变量，或直接将后缀为 `.spr` 的代码文件放在解释器同一目录下，执行如下命令即可运行代码：

```shell
./spiral input.spr
```

## 支持的语言特性

- 使用 `def` 关键字进行变量定义
- 使用 `if` `else` 关键字编写选择结构
- 使用 `while` `do while` `for` 关键字编写循环结构
- 使用 `print` 关键字进行打印
- 加减乘除、取余等基本数值运算
- 通过 `{}` 完成的作用域控制
- 弱类型系统，支持整形、浮点型及字符串类型的变量
- 支持 `break` `continue` `return` 关键字
- 通过 `function` 关键字定义函数，支持基础的函数闭包功能

## 使用的第三方库

- Antlr 3.4
