# Leiva, the definitive low-level programming language
## Download & Installation
There are not actual releases, since this language is a prototype. 

## How Leiva works:
Leiva is written in [Go](https://golang.org/) and the compiled with [gcc](https://github.com/gcc-mirror/gcc). The interpreter and the translater of Leiva is written in Go, then the compilation process takes place in C.

###### Translater:
The translater is in charge of converting the Leiva language into C language and then, compile it with gcc. That gives Leiva, the powerful syntax of it and the power an speed of C.

## Compilation

#### If you want to interpret your code use:
```
leiva main.lei
```

#### If you want to compile and create an executable of your code use:
```
leiva build main.lei -o executable
```

## Examples
#### Hello World:
```julia
println("Hello World!!!")
```
```
Hello World!!!
```
#### Fibbonacci numbers:
```julia
fn fibb(n)
  if n == 0 or n == 1
    return 1
  else 
    return fibb(n - 1) + fibb(n - 2)

fn main()
  for i in range 10
    if i == 10 print(fibb(i)) else print(fibb(i) + ", ")


```
```
0, 1, 1, 2, 3, 5, 8, 13, 21, 34
```

#### Object Oriented:
```julia
struct OwnArray<T>
  priv data: []T
  
  pub constr(data: []T)
    self.data = data
  
  pub constr(data: ... T)      # In order to put infinite arguments
    for val in data
      *(self.data++) = val
    
  pub fn size()
    return data.size()
    
  pub operator self()
    return self.data
    
    
fn main()
  a = OwnArray<i32>([1, 2, 3]) # 1st constructor
  b = OwnArray<i32>(1, 2, 3)   # 2nd constructor
  
  println(a + ", " + b)
  
```
```
[1, 2, 3], [1, 2, 3]
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
