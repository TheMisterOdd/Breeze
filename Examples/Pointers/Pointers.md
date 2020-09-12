# Pointers

### How to define a pointer?
```julia
fn main() 
{
  i, j = 40, 21

  p = &i         # point to i
  println(*p) # read i through the pointer
  *p = 21         # set i through the pointer
  println(i)  # see the new value of i

  p = &j         # point to j
  *p = *p / 7   # divide j through the pointer
  println(j) # see the new value of j
}
```

##### Output:
```
40
21
3
```

### Heap allocation:
```julia
struct Vector2<T> 
{
  pub var x: T, y: T
}
  

fn main() 
{
  vec1 = &Vector2<f32> # Create an object in the heap memory. The '&' allows this.
  vec.x = 1
  vec.y = 2
  
  # also, you could alloc memory like this
  vec2 = &Vector<f32>{1, 2}
  
}
```
###### You may find interesting: 
[Heap Memory](https://en.wikipedia.org/wiki/Memory_management#HEAP)
