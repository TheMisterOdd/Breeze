# Type, structs, enums and interfaces
### Type:
```
package main

type NameSaver string

fn main()
    n NameSaver = "Paula"
end
```
### Structs:
```
-- circle.lei --
package circle

import "math"

type Circle struct
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
### Interfaces:
```
-- polygon.lei --
package polygon

import "math"

type Polygon interface
    Area() f64
    Perimeter() f64
end

fn Area(p Polygon) f64
    return p.Area()
end

fn Perimeter(p Polygon) f64
    return p.Perimeter()
end

type Square struct
    side f64
end

fn (s Square) Area() f64 // the compiler automatically knows that 'Square' is a child from 'Polygon'
    return s.side * s.side
end

fn (s Square) Perimeter() f64
    return s.side * 4
end

type Circle struct
    radius f64
end

fn (c Circle) Area() f64
    return c.radius * c.radius * math.Pi
end

fn (c Circle) Perimeter() f64
    return c.radius * c.radius * math.Pi
end

-- main.lei --
package main

import "polygons"

fn main()
    s := Square{ 4 }
    c := Circle{ 3 }
    
    res0 := Area(s)
    res1 := Area(c)
    
    println(res0, res1)
end
```
