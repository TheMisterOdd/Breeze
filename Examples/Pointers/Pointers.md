# Pointers

### How to define a pointer?
```julia
fn main()
  i, j = 40, 21

  p = &i         # point to i
  println(*p) # read i through the pointer
  *p = 21         # set i through the pointer
  println(i)  # see the new value of i

  p = &j         # point to j
  *p = *p / 7   # divide j through the pointer
  println(j) # see the new value of j
```

##### Output:
```
40
21
3
```
