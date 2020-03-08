# Leiva, the definitive low-level programming language
### Download & Installation
There are not actual releases, since this language is a prototype. 

### Examples
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
