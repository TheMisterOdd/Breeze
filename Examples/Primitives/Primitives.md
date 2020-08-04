# Primitives variables
### Scalar Types
- signed integers: ```i8```, ```i16```, ```i32```, ```i64```, ```i128``` and ```size (pointer size)```
- unsigned integers: ```u8```, ```u16```, ```u32```, ```u64```, ```u128```
- floating point: ```f32```, ```f64```
- character scalar  ```char``` and ```string```. Also the ```string``` variable is an ```[]char``` (an array of ```char```)
- ```bool``` either ```true``` or ```false```
- The unit / void type ```unit```, whose only possible value is an empty touple: ```()```

```julia

x: i8 = 255 # Maximun capacity of an i8   # NOTE: x = 256 will print an error of exceded capacity of an i8
print(x) # i8 variable

# If you put:
println(i8.Max()) # It prints you the size that an specific varible type can support, in this case i8

logic: bool = true # Logical operator
println(logic)

str = "String" # string variable, it could be also defined 'str: string = "String"' or  'str: []char = "String"'
println(str)

a = 1.0 # This is an 'f64'
println(a)

pi = 3.1415f # The 'f' at the end of the number indicates that the variable is a floating number (f32)
println(pi)

```

##### Output:
```
255
256
true
String
1.0
3.1415
```

### Compound Types
- arrays: ```[1, 2, 3]```, also could be defined as ```var = [...]``` or ```var: [S]T = [...]```, where ```T``` is the type of variable that is going to be stored and ```S``` is the size of the array.
- lists: ```{1, true, 3.14f}```
- tuples: ```(1, 0, 11, 2231)```
- memory blocks: ```interface{}```, also know as ```unsafe pointer``` and the equivalent in C is ```void*```

```julia

array1: []i32 = [1, 2, 3] # If you don't put anything inside '[]' before the 'i32', the code will create a dynamic allocated array
# or
array2 = [] # Null array
println(array1)
println(array2)

```

##### Output:
```
[1, 2, 3]
[]
```
