# Type, structs, enums and interfaces
### Type:
### Structs:
```
-- circle.lei --
package circle

import "math"

struct Circle
    diameter u32 // lowercase-starting variables are hidden to the user
    Radius u32 // uppercase-starting variables are public to the user
end

fn New(radius u32) *Cube
    return &Cube { radius * 2, radius }
end

fn (c Cube) Area() f64
    return math.Pi * c.Radius * c.Radius
end

fn (c Cube) Perimeter() f64
    return math.Pi * 2.0 * c.Radius
end

-- math.lei --
package main

import "circle"

fn main()
    c *circle.Circle = circle.New(1)
    println(c.Area(), c.Perimeter())
end
```

