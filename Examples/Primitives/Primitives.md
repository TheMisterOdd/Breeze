# Primitives variables
### Scalar Types
- signed integers: ```i8```, ```i16```, ```i32```, ```i64```, ```i128``` and ```isize (pointer size)```
- unsigned integers: ```u8```, ```u16```, ```u32```, ```u64```, ```u128``` and ```usize (pointer size)```
- floating point: ```f32```, ```f64```
- unicode scalar  ```char```(4 bytes each)
- ```bool``` either ```true``` or ```false```
- The unit type ```unit```, whose only possible value is an empty value


### Compound Types
- arrays: ```[1, 2, 3]```, also could be defined as ```Array<T, S> = [...]```, where ```T``` is the type of variable that is going to be stored and ```S``` is the size of the array.
- lists: ```{1, true, 3.14f}```

```julia

array1: Array<> = [1, 2, 3] 
# or
array2 = []
println(array1)
println(array2)

```

### Output:
```
'[1, 2, 3]'
'[]'
```
