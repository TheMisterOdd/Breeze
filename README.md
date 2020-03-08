# Leiva, the definitive low-level programming language
## Download & Installation
There are not actual releases, since this language is a prototype. 
## Compilation

#### If you want to interpret your code use:
```
leiva [input_file] [arguments]
```

#### If you want to compile and create an executable of your code use:
```
leivac [input_file] -o [output_file] [arguments]
```

## Examples
#### Hello World:
```rust
println("Hello World!!!")
```
#### Fibbonacci numbers:
```rust
fn fibb(n)
  if n == 0 or n == 1
    return 1
  else 
    return fibb(n - 1) + fibb(n - 2)
  ;
;

fn main()
  for i in range 10
    put(fibb(i))
  ;
;

```
A hipotetical new programming language. Syntax and functions are prototypes.
