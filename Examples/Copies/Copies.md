# Primitives variables
### Copy functions:

```julia
a = 10
b = a # This is a type of copy
# also:
memcpy(&b, &a, size(a)) # another way of copy (recomended for copying pointers)

# Pointers do not copy, only a reference is created, for example:
x: *i32 # creates a pointer of 'i32'
*x= 10 # assings an specific value to the pointer

y = x # WARNING!!! This only create a reference to the pointer

print(*x) # Prints the value of the pointer of 'x'
print(*y) # Also prints the value of the pointer 'x'

delete y # NOTE: Since 'y' is a reference this will also delete 'x'



```
