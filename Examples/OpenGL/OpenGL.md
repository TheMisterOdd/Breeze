# OpenGL
### Libraries
- Window Managment and context: [```glfw```](), [```SDL```](), [```SFML```]()
- OpenGL: [```glew```](), [```glad```](), [```gl3w```]()

###### Note: We will use external bindings from C in order to use it in Leiva, concretly, I'll use GLFW and glad.

### Creation of window with classes:
```julia

import extern "glfw/glfw3.h" # The 'extern' keyword indicates that we are importing 
import extern "glad/glad.h"  # something directly from C or C++ and maybe in further updates from other languages

struct Window {
  pub var width: i16, height: i16, fullscreen: bool
  pub var window: GLFWwindow*
  pub var vidMode: GLFWVideoMode*
  
  pub constr(width: i16, height: i16, title: string, fullscreen: bool) 
  {
    self.width, self.height = width, height
    self.fullscreen = fullscreen
    
    if !glfwInit()
      throw "Error, could not create a GLFW contex"
    
    self.window = glfwCreateWindow(width, height, title, if fullscreen glfwGetPrimaryMonitor() else null, null)
    if !self.window
      throw "Error, cannot not create a GLFW window"
    
    self.vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor())
    glfwSetWindowPos(self.window, (self.vidMode.width - self.width) / 2, (self.vidMode.height - self.height) / 2)
   
    glfwMakeContextCurrent(self.window)
   
    if !gladLoadGL()
      throw "Error, cannot not create a OpenGL window"
   
    println("GLFW " + glfwGetVersionString())
    println("OpenGL " + glGetString(GL_VERSION))
    println("GLSL " + glGetString(GL_SHADING_LANGUAGE_VERSION))
    println(glGetString(GL_VENDOR))
    println(glGetString(GL_RENDERER))
  }   
}
```
