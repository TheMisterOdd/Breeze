#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct 
{
  int16_t width, height;
  bool fullscreen;
  
  GLFWwindow* window;
  GLFWvidMode* vidMode;
} Window;

Window WindowConstructor(int16_t width, int16_t height, const char* title, bool fullscreen) 
{
  Window window;
  
  if (!glfwInit()) 
  {
    fprintf(stderr, "Error, cannot not create a GLFW window")
    return -1;
  }
  
  self.window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetMonitor() : NULL, NULL);
  if (!self.window) 
  {
    fprintf(stderr, "Error, cannot not create a GLFW window")
    return -1;
  }
  
}

int main(void) 
{
  if (!glfwInit()) 
  {
    
  }
  GLFWwindow* window = glfwCreateWindow()
}
