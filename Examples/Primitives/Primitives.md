# Primitives variables
### Scalar Types
- signed integers: ```i8```, ```i16```, ```i32```, ```i64```, ```i128``` and ```isize (pointer size)```
- unsigned integers: ```u8```, ```u16```, ```u32```, ```u64```, ```u128``` and ```usize (pointer size)```
- floating point: ```f32```, ```f64```
- unicode scalar  ```char``` and ```string```. Also the ```string``` variable is an ```[]char``` (an array of ```char```)
- ```bool``` either ```true``` or ```false```
- The unit type ```unit```, whose only possible value is an empty value

```julia

x: i8 = 255 # Maximun capacity of an i8
x = 256     # Error, exceded capacity of an i8

# If you put:
println(i8.size()) # it prints you the size that an specific varible type can support, in this case i8

```

##### Output:
```
256
```

### Compound Types
- arrays: ```[1, 2, 3]```, also could be defined as ```var = [...]``` or ```var: [S]T = [...]```, where ```T``` is the type of variable that is going to be stored and ```S``` is the size of the array.
- lists: ```{1, true, 3.14f}```

```julia

array1: []i32 = [1, 2, 3] #if you don't put anything inside '[]', the code will create a dynamic allocated array
# or
array2 = []
println(array1)
println(array2)

```

##### Output:
```
[1, 2, 3]
[]
```
