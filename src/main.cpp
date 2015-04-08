#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"

#if _DEBUG
#include <iostream>
#endif

int main()
{
  if (!glfwInit())
  {
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(512, 512, "Block Game", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

#if _DEBUG
  std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << std::endl;
#endif

  if (glewInit() != GLEW_OK)
  {
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  double time = 0;
  double new_time;
  double delta;

  int width;
  int height;

  block_game::World world;

  while (!glfwWindowShouldClose(window))
  {
    new_time = glfwGetTime();
    delta = new_time - time;
    time = new_time;
    world.Update(delta);

    glfwGetFramebufferSize(window, &width, &height);

    world.Display(width, height);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
