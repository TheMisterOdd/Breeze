# Primitives variables
### Copy functions:

```
package main

fn main()
    a, b := 10, 52
    println(a, b) 
    copy(&a, &b) // 'copy' is a built-in function, so there is no need to import anything.
    println(a, b)
   
    println() // add a new line

    // also works with slices:
    str0, str1 := "Hello", "World"
    println(str0, str1)
    copy(str0, str1) // don't need to use '&' as before, because slices are pointers
end
```

##### Output:
```
10 52
52 52

Hello World
World World
```
