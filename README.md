# Leiva, the definitive low-level programming language
## Download & Installation
There are not actual releases, since this language is a prototype. 

## How Leiva works:
Leiva is written primary in C++ and its resultant code is compiled with [gcc](https://github.com/gcc-mirror/gcc). This gives Leiva a powerful typed and the speed and the low-level of C.

##### How it works?
**compiler:**
```
leiva
  └─ front-end
        └─ translation to C
             └─ gcc compiles the C source code
                  └─ executable
```

## Compilation

#### If you want to compile and create an executable of your code use:
```
leiva build main.lei <args> -o [executable_name]
```

## Examples
#### Hello World:
```
fn main() {
    println("Hello World!!!")
}
```
```
Hello World!!!
```
#### Fibbonacci numbers:
```
fn fib(n i32) -> i32 {
  if n <= 1 {
    return n
  }
  else {
    return fib(n - 1) + fib(n - 2)
  }
}
  

fn main() {
  for i := 0; i < 10; i++ {
    print(fib(i), "")
  }
}

```
```
0 1 1 2 3 5 8 13 21 34
```

#### Double return:
```
fn swap(a, b &GenericType) {
  a, b = b, a
}
  

fn pair() -> ([]i32, string) { 
  return i32[], "Here I return an array to you."
}

fn main() {
  a, b := 10, 6

  println(a, b) // Before
  swap(a, b)
  println(a, b, "\n") // After

  arr, str := pair()
  println(arr)
  println(str)
}
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

struct OwnArray {
  data []any // variables with a lowercase starting letter, will be private.
}

impl OwnArray {
  fn String(self &OwnArray) -> string {
    return self.data
  }
}


-- main.lei --
package main

import "array"

fn main() {
  
  a := array.array {[]i32 {1, 2, 3}}
  b := []i32{1, 2, 3}
  
  println(a)
  println(b)
  
}
  
```
```
[1, 2, 3] 
[1, 2, 3]
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
