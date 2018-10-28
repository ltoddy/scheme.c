<div align="center">
    <h1>A Scheme interpreter.</h1>
    <p>
      <a href="https://github.com/ltoddy/scheme.c/blob/master/LICENSE"><img src="https://img.shields.io/github/license/ltoddy/scheme.c.svg" alt="LICENSE"></a>
      <a href="https://github.com/ltoddy/scheme.c/stargazers"><img src="https://img.shields.io/github/stars/ltoddy/scheme.c.svg" alt="stargazers"></a>
      <a href="https://github.com/ltoddy/scheme.c/releases/tag/v0.1.0"><img src="https://img.shields.io/badge/release-v0.1.0-green.svg" alt="release"></a>
    </p>
    <img src="assets/illya.gif"/>
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

### 不支持浮点数运算,难度不小(其实是懒).
