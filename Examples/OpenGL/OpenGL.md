# OpenGL
### Libraries
- Window Managment and context: [```glfw```](), [```SDL```](), [```SFML```]()
- OpenGL: [```glew```](), [```glad```](), [```gl3w```]()

###### Note: We will use external bindings from C in order to use it in Leiva, concretly, I'll use GLFW and glad.

### Creation of window with classes:
```julia

import extern "glfw/glfw3.h" # The 'extern' keyword indicates that we are importing 
import extern "glad/glad.h"  # something directly from C or C++ and maybe in further updates from other languages

import mem

fn main(args: []string) 
{
  if not glfwInit() 
    throw &RuntimeException("Cannot create a GLFW context")
  
  window = glfwCreateWindow(1280, 720, "", null, null);
  if window == null
    throw &RuntimeException("Cannot create a GLFW window context")
  
  glfwMakeContextCurrent(window)
  
  if not gladLoadGL()
    throw &RuntimeException("Cannot create a OpenGL context")
  
  vertices = [ 
    # Positions:
    -1.0f, -1.0f, +0.0f,
    +1.0f, -1.0f, +0.0f,
    +1.0f, +1.0f, +0.0f,
    -1.0f, +1.0f, +0.0f,
  ]
  
  var buffer: u32
  glGenBuffers(1, &buffer)
  glBindBuffer(GL_ARRAY_BUFFER, buffer)
  glBufferData(GL_ARRAY_BUFFER, mem.sizeof(vertices) * vertices.lenght(), &vertices)
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, f32.bytes() * 3, static_cast<&()>);

  
  while not glfwWindowShouldClose() 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPHT_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    
    
    glfwWindowSwapBuffers(window); 
    glfwPollEvents();
  }
  
}

```
