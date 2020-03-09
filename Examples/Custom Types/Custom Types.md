# Primitives variables
### Custom Types
- ```struct```: used to define a structure
- ```enum```: used to define an enumeration

Constants can also be created via the ```const``` and ```static``` keywords.

#### Constructors:
- The structs, can have a [constructor](https://en.wikipedia.org/wiki/Constructor_(object-oriented_programming)) or not, for example:
```julia

struct vec3_ # without constructor
  x: f32
  y: f32
  
struct vec3 # with constructor
  x: f32
  y: f32
  
  constr(x, y) # this is how the constructor is defined, is like a normal function, but it will called once you create an struct (if it has one)
    self.x = x # this will save the values you put in the correspondant variables
    self.y = y
  
a = vec3_{1, 2} # this is how you create a struct without a constructor 

# NOTE: here you must define all the values inside the struct in order or putting the 
# name of the variable before the value, for example: "vec3_{y=2, x=1}"

b = vec3(1, 2) # this is how you create a struct with a constructor

```

#### Some ```std``` structs are:

##### ```string```
```julia

struct string
  priv iterator<string>
  priv lenght
  priv data: []char
  
  pub constr(&data: []char)
    memcpy(self.data, data, size(data))
    self.lenght = size(self.data[0]) / size(self.data)
  
  pub constr(&data: string)
    memcpy(self.data, data, size(data))
    self.lenght = size(self.data[0]) / size(self.data)
    
  [...]
  
  pub const fn lenght()
    return self.lenght
  
  [...]
  
  pub static fn copy(&dest: string, &data: string)
    memcpy(dest, data, size(data))
    self.lenght = size(self.data[0]) / size(self.data)
  
  [...]
  
# Example:
s1 = string("Hello World!!!")
s2 = string("Bye, Bye!!!")

println(s1)
println(s2)

string.copy(s1, s2)

println(s1)
println(s2)

```

##### Output:
```
Hello World!!!
Bye, Bye!!!
Bye, Bye!!!
Bye, Bye!!!
```
