# Primitives variables
### Scalar Types
- signed integers: ```i8```, ```i16```, ```i32```, ```i64```, ```i128``` and ```isize (pointer size)```
- unsigned integers: ```u8```, ```u16```, ```u32```, ```u64```, ```u128``` and ```usize (pointer size)```
- floating point: ```f32```, ```f64```
- character scalar  ```char``` and ```string```. Also the ```string``` variable is an ```[]char``` (an array of ```char```)
- ```bool``` either ```true``` or ```false```
- The unit / void type ```unit```, whose only possible value is an empty touple: ```()```

```
package main

import "math"

fn main()
    x u8 = 255  // variable that can hold 8 bits of int data.
    println(x)
    
    println(math.MaxUint8)  // maximun value that a 'u8' can hold
    
    b bool = true // boolean, can be either true or false
    println(b) 

    str string = "This is a string" // chain of characters
    println(str)
    
    f f64 = 3.71 // floating point variable, can hold 8 bytes of data
    println(f)

    pi f32 = 3.1415F // the f at the end of the number indecates that is a 4 bytes floating point variable
end
```

##### Output:
```
255
256
true
This is a string
3.71
3.1415
```

### Compound Types
- arrays: ```[]i32 {1, 2, 3}```, also could be defined as ```var = [...]``` or ```var: [S]T = [...]```, where ```T``` is the type of variable that is going to be stored and ```S``` is the size of the array.
- memory blocks: ```interface{}```, also know as ```unsafe pointer``` and the equivalent in C is ```void*```

```julia

array1 := []i32{1, 2, 3} # If you don't put anything inside '[]' before the 'i32', the code will create a dynamic allocated array
# or
array2 = []i32{} # Null array
println(array1)
println(array2)

```

##### Output:
```
[1, 2, 3]
[]
```
