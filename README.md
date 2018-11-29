<div align="center">
    <h1>A Scheme interpreter.</h1>
    <p>
      <a href="https://github.com/ltoddy/scheme.c/blob/master/LICENSE"><img src="https://img.shields.io/github/license/ltoddy/scheme.c.svg" alt="LICENSE"></a>
      <a href="https://github.com/ltoddy/scheme.c/stargazers"><img src="https://img.shields.io/github/stars/ltoddy/scheme.c.svg" alt="stargazers"></a>
      <a href="https://github.com/ltoddy/scheme.c/releases/tag/v0.1.0"><img src="https://img.shields.io/badge/release-v0.1.0-green.svg" alt="release"></a>
    </p>
</div>

*来源SICP(Structure and Interpretation of Computer Programs)第四章开始的元解释器的教学*

## Overview

    程序设计语言的设计不应该是特征的堆砌,而应消除那些需要依赖于多余特征的弱点和局限.
    Scheme语言证明,极少的表达式构造规则和不加限制的表达式复合方式可以构造出实用而高效的程序设计语言,
    其灵活性足以支持今天的大部分主流编程模型.

    Scheme是最早的像在lambda演算里一样提供了第一级过程的程序设计语言之一,
    并由此在动态类型的语言中提供了有用的静态作用域规则和块结构的特征.
    在Lisp的主要方言中,Scheme第一次使过程有别于lambda表达式和符号,
    为所有变量使用单一的词法环境,在确定运算符的位置时采用与确定运算对象位置一样的方式.
    Scheme完全依赖过程调用来表示迭代,并以此强调,尾递归过程调用在本质上就是传递参数的goto.
    Scheme是第一种被广泛使用的,采纳第一级逃逸过程(escape procedure)的程序设计语言,
    通过第一级逃逸过程可以合成所有已知的顺序控制结构.
    Scheme的后续版本引入了精确和非精确数的概念,这是CommonLisp语言通用算术功能的扩展.
    最近,Scheme成为了第一种支持卫生宏(hygienic macro)的程序设计语言,
    该机制允许我们以一种一致和可靠的方式扩展块结构语言的语法.

### Quick Start

<a href="https://asciinema.org/a/182762" target="_blank">
  <img src="https://asciinema.org/a/182762.png" alt="Quick Start" width="240" height="180" border="10"/>
</a>

### usage

```
$ cmake .
$ make
$ ./bin/scheme
Welcome to Scheme. Use ctrl-c to exit.
> (apply + '(1 2 3))
6
> (and 1 2 #f 3)
#f
>  (or #f #f 3 #f)
#t
> (let ((x (+ 1 1))
        (y (- 5 2)))
       (+ x y))
5
> (define (sum x y) (+ x y))
ok
> (sum 10 20)
30
> ((lambda (x) x) 1)
1
> sum
#<procedure>
> (define c ((lambda (x) (lambda () x)) 3))
ok
> (c)
3
> (quote ())
()
> (quote (0 . 1))
(0 . 1)
> (quote (1 2 3 4))
(1 2 3 4)
> (quote abcd)
abcd
> (define a 1)
ok
> (set! a 2)
ok
> a
2
> (if #t 1 2)
1
> (if #f 1 2)
2
> (+ 4 5 6)
15
> (define env (environment))
ok
> (eval '(define a 250) env)
ok
> (eval 'a env)
250
> ^C
```

### 支持一些函数式feature

```
> (define (currying-sum x)
      (lambda (y) (+ x y)))
ok
> ((currying-sum 10) 20)
30
> (define (length lst)
    (define (iter lst count)
      (if (null? lst)      
          count
          (iter (cdr lst) (+ count 1))))
    (iter lst 0))
ok
> (length '(1 2 3))
3
```

### Install:

> sudo ./INSTALL

### Require

gcc

cmake version >= 3.10

如果你的cmake版本低,请去修改*CMakeLists.txt*文件第一行的需求版本.

### Document:

[Here](docs/README.md)

### [CHANGELOG](./CHANGELOG.md):

#### v:0.1.0 : 2018.05.23 (May 23, 2018)

  - control structure and built-in process
  - primitive procedures
  - basic type


### TODO

- 浮点数运算的支持(目前还不支持浮点数运算,难度不小(其实是懒))
- 错误处理(目前遇到错误,比如语法错误,是exit的,要改成ignore那个expression)
- 垃圾自动回收机制, gc模块
- r5rs的支持
- r6rs的支持
- 解释文件 e.g. ->  scheme -f main.scm
- 添加m4,自循环编译文件
- 用户自定义数据结构(struct关键字)
- 宏(由于lisp的同相性,所有才能有宏这个东西,宏在编译期转换成lisp代码)

### 本解释器built-in的结构:

在 `scheme/builtin.c` (在`void PopulateEnvironment(SchemeObject* env)`中) 中, 我定义了一个宏:

```c
#define ADD_PRIMITIVE(scheme_name, c_name) \
    DefineVariable(MakeSymbol(scheme_name), MakePrimitiveProc(c_name), env);
```

然后有一大堆对这个宏的使用.

除了这部分, 还有在`main.c`中

```c
SchemeObject* stdlib = AllocObject();
   ...
LoadProcedure(stdlib);
```

这会加载 `lib/builtin.scm` 中定义的函数.

未来如果要扩展更大的标准库, 可以将 `lib/builtin.scm` 改为例如:

```
(load "string")

(load "char")

(load "io")

....
```
