# Breeze, the definitive low-level programming language
## Download & Installation
There are not actual releases, since this language is a prototype. 

## How Breeze works
Breeze is written primary in C++ and the Breeze's source code is translated into C and compiled with [g++](https://github.com/g++-mirror/g++) (might port to LLVM in the future). This gives Breeze a powerful typed and the speed and the low-level of C.

Breeze is strongly influenced by Go and C (but mostly Go). But you'll ask... If is based in Go, why you don't use Go instead?

**various reasons:**
* Go only allows, manual memory allocation, but no deallocation. Breeze is focus on embedded systems, so I also want manual deallocation of memory while keeping simple the development.

* Make it more simple by removing not needed keywords such as ```var``` for defining variables. Variable creation would look like this ```t Type``` instead of ```var t Type```

* Improve performamce by using GCC as the backend of the compiler. Also promoting the use of optimization flags: `-O2`, `-Os`, `-s`... for better optimized code than, Go's.

* C is embedded into the language. You could simple call a C function or the C preprocesor with an '@': `@#include <math.h>` or `@sin(90)`

* Inlining. Don't need to call a function if you copy it's code into the source code, directly, whenever is called. This saves, time by avoiding function call overhead. Functions defined like this: `fn Sin(x f64) f64 = @sin(math.Deg(x))` will be inlined

* Built-In basic `print` and `println`. Also supports format by using `string` formatting.

* More...

##### How it works?
**compiler:**
```
Breeze
  └─ front-end
        └─ translation to C
             └─ gcc compiles the C source code
                  └─ executable
```

## Compilation

#### If you want to compile and create an executable of your code use:
```
breeze c <args> -o [executable_name]
```
**NOTE**: the `build` argument, gets all the `.lei` files at the directory, for compiling them.
## Examples
#### Hello World:
```
package main

proc main()
  println("Hello World!!!")
end
```
```
Hello World!!!
```
#### String Format:
```
package main

proc main()
  x := 1279
  str := "Value of x is $x"
    
  println("{}", str)
end
```
```
Value of x is 1279
```
#### Fibbonacci numbers:
```
proc fib(n u64) u64 
  if n <= 1
    return n
  end
  return fib(n - 1) + fib(n - 2)
ens
  

proc main()
  for i := 0; i < 10; i++
    print(fib(i), "")
  end
end

```
```
0 1 1 2 3 5 8 13 21 34
```

#### Double return:
```
proc swap(a, b &Any)
  a, b = b, a
end
  

proc pair() ([]i32, string)
  return []i32{}, "Here I return an array to you."
end

proc main()
  a, b := 10, 6

  println(a, b) // Before
  swap(a, b)
  println(a, b, "\n") // After

  arr, str := pair()
  println(arr)
  println(str)
end
```
```
10 6
6 10

[]
Here I return an array to you.
```

#### Object Oriented:
```
-- array.lei --
package array
OwnArray struct
  data []any // variables with a lowercase starting letter, will be hidden
end

proc (a OwnArray) String() string
  return string(a.data)
end


-- main.lei --
package main

import "array"

proc main()
  
  a := array.OwnArray {[]i32 {1, 2, 3}}
  b := []i32{1, 2, 3}
  
  println(a)
  println(b)
  
end
  
```
```
[1, 2, 3] 
[1, 2, 3]
```
#### Coroutines:
```
package main

proc fib(n u64, c chan u64)
  x, y := 0, 1
  for i := 0; i < n; i++
    c <- x
    x, y = y, x + y
  end
  close(c)
end

proc main()
  c := make(chan u64, 16)
  rout := run fib(16, c)

  for n := range c
    println(<- c)
  end
  join(rout) // join the routine
end
```
## Leiva by examples:
| Nº            | Tutorial      | Complexity      |
| ------------- |:-------------:|:---------------:|
| 1             | [Hello World!!!](https://github.com/AlKiam/Leiva/tree/master/Examples/Hello%20World) | Easy |
| 2             | [Primitives](https://github.com/AlKiam/Leiva/tree/master/Examples/Primitives) | Easy |
| 3             | [Pointers](https://github.com/AlKiam/Leiva/tree/master/Examples/Pointers) | Medium |
| 4             | [Custom types](https://github.com/AlKiam/Leiva/tree/master/Examples/Custom%20Types) | Easy |

###### Note:
A hipotetical new programming language. Syntax and functions are prototypes.
