#ifndef SCHEME_C_GC_H
#define SCHEME_C_GC_H

#include "object.h"

// TODO
/**
 * @param environment
 * 这个 scheme interpreter 中所有的东西, 无论是数字: 1, 2, 3 还是复杂的对象, 都是转换成 SchemeObject* (scheme/object.j) 指针.
 * 也就是说, 所有对象都是从堆中分配内存, 而非栈中.
 *
 * 关于环境:
 * e.g.
 * ```scheme
 * (define g1 ...)
 *
 * (define (foo arg1 arg2 ...)
 *   (let ((l1 ...)
 *         (l2 ...))
 *     (...)))
 * ```
 * 在foo函数的最里层的环境大致样子为:
 * (((l1 ...) (l2 ...) (arg1 ...) (arg2 ...)) g1 ...)
 * |||               |                      |       |
 * |||let local scope|                      |       |
 * ||              define scope             |       |
 * |                global scope                    |
 * 他会从当前环境向外层去寻找 var 对应的 val (scheme/environment.c LookupVariableValue 函数)
 * 但是目前还没有实现gc模块,也就是所,假设有两个函数,每个函数都有各自的environment,但是厉害作用域之后,
 * 环境中申请的内存并不会被回收.
 *
 * ## 下一步:
 * 先实现引用计数回收
 * 在 SchemeObject 结构体中添加引用计数器: unsigned short ref_count.
 * 修改解释器,当离开作用域的时候,启动gc,回收作用域中的内存块.
 * 关于递归作用域回收问题:虽然我的eval(scheme/eval.c)函数对于递归转换成了goto语句,但是我还不确信......
 */
extern void collect(SchemeObject* environment);

#endif //SCHEME_C_GC_H
