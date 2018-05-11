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
> #f
#f
> 123
123
> -123
-123
> 003
3
> #\c
#\c
> "abc"
"abc"
> "a

   bbsd"
"a\n\n   bbsd"
> ()
()
> ac
ac
> (quote ())
()
> (quote (0 1))
(0 1)
> (quote (0 . 1))
(0 . 1)
> (quote (1 2 3 4))
(1 2 3 4)
> (quote abcde)
abcde
> ^C
```
