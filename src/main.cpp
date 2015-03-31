#include "glew/glew.h"
#include "glfw/glfw3.h"

#include "game/world.h"

int main()
{
  if (!glfwInit())
  {
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(512, 512, "BlockGame", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

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
    glViewport(0, 0, width, height);

    world.Display();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
