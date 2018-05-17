cmake_minimum_required(VERSION 3.10)
project(scheme_c C)

set(CMAKE_C_STANDARD 90)

add_executable(
        scheme_c
        main.c
        scheme/object.c scheme/object.h
        scheme/type.c scheme/type.h
        scheme/read.c scheme/read.h
        scheme/write.c scheme/write.h
        scheme/eval.c scheme/eval.h
        scheme/builtin.c scheme/builtin.h
        scheme/environment.c scheme/environment.h
        scheme/assignment.c scheme/assignment.h
        scheme/define.c scheme/define.h
        scheme/if.c scheme/if.h
        scheme/predicate.c scheme/predicate.h
        scheme/procedure.c scheme/procedure.h
        scheme/lambda.c scheme/lambda.h
        scheme/begin.c scheme/begin.h
)
