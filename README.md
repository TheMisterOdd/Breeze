# Leiva, the definitive low-level programming language
## Download & Installation
There are not actual releases, since this language is a prototype. 
## Compilation

#### If you want to interpret your code use:
```
leiva main.lei
```

#### If you want to compile and create an executable of your code use:
```
leivac main.lei -o
```

## Examples
#### Hello World:
```python
println("Hello World!!!")
```
#### Fibbonacci numbers:
```python
fn fibb(n)
  if n == 0 or n == 1
    return 1
  else 
    return fibb(n - 1) + fibb(n - 2)

fn main()
  for i in range 10
    print(fibb(i))

```

#### Object Oriented:
```
struct OwnArray<T>
  priv data: []T
  priv lenght: u64
  
  constr(data: []T)
    self.data = data
  
  constr(seq: Seq<T>)
    self.data = []seq // Transforms from 'Seq<T>' to 'Array<T>'
  
```
A hipotetical new programming language. Syntax and functions are prototypes.
