## compound procedures

```
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
```


## primitive procedures

* null?

```scheme
> (null? "a")
#f
> (null? 1)
#f
> (null? '())
#t
```

* boolean?

```scheme
> (boolean? 1)
#f
> (boolean? #f)
#t
```

* symbol?

```scheme
> (symbol? 'a)                   
#t
> (symbol? "a")
#f
```

* integer?

```scheme
> (integer? 10)
#t
> (integer? "10")
#f
> (integer? '10)
#t
```

* char?

```scheme
> (char? #\a)
#t
> (char? 'a)
#f
```

* string?

```scheme
> (string? "abc")
#t
> (string? 'abc)
#f
```

* pair?

```scheme
> (define c (cons 1 2))
ok
> (pair? c)
#t
```

* procedure?

```scheme
> (procedure? +)
#t
> (procedure? procedure?)
#t
```

* number->string
* string->number

```scheme
> (number->string 10)
"10"
> (number->string 123456789)
"123456789"
> (string->number "123456789")
123456789
> (string->number "0123")
123
```

* symbol->string
* string->symbol

```scheme
> (symbol->string 'abc)
"abc"
> (string->symbol "abc")
abc
```

* char->integer
* integer->char

```scheme
> (char->integer #\a)
97
> (integer->char 97)
#\a
```

* \+
* \-
* \*

```scheme
> (+ 1 2 3 4 5)
15
> (- 10 4 3)
3
> (* 1 2 3 4)
24
```

* quotient
* remainder

```scheme
> (quotient 10 3)
3
> (remainder 10 3)
1
```

* =
* <
* \>

```scheme
> (= 10 10)
#t
> (> 20 10)
#t
> (< 3 5)
#t
```

* cons
* car
* cdr
* set-car!
* set-cdr!

```scheme
> (define c (cons 10 20))
ok
> (car c)
10
> (cdr c)
20
> (set-car! c 100)
ok
> (set-cdr! c 200)
ok
> c
(100 . 200)
> 
```

* list

```scheme
> (list 1 2 3)
(1 2 3)
```

* eq?

```scheme
> (define o1 10)
ok
> (define o2 10)
ok
> (eq? o1 o2)
#t
```

* begin
```scheme
> (begin 1 2)
2
```

* cond
```scheme
> (cond (#f 'false) (else 'true))
true
```

* let
```scheme
> (let ((x (+ 1 1))
        (y (- 5 2)))
       (+ x y))
5
```

* and
* or
```scheme
> (and 1 2 #f 3)
#f
>  (or #f #f 3 #f)
#t
```

* apply
```scheme
> (apply + '(1 2 3))
6
```
