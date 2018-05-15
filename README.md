<div align="center">
    <h1>A Scheme interpreter.</h1>
    <img src="assets/illya.gif"/>
</div>

### usage

```
$ cmake .
$ make
$ ./scheme_c
Welcome to Scheme. Use ctrl-c to exit.
> #t
#t
> #\c
#\c
> "abc"
"abc"
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
> ^C
```

### Document:

[Here](docs/README.md)
