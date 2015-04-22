#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"

#if _DEBUG
#include <iostream>
#endif

block_game::World* world;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_LEFT_BRACKET)
    {
      world->set_camera_delta_roll(1.0F);
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET)
    {
      world->set_camera_delta_roll(-1.0F);
    }
    else if (key == GLFW_KEY_UP)
    {
      world->set_camera_delta_pitch(-1.0F);
    }
    else if (key == GLFW_KEY_DOWN)
    {
      world->set_camera_delta_pitch(1.0F);
    }
    else if (key == GLFW_KEY_LEFT)
    {
      world->set_camera_delta_yaw(-1.0F);
    }
    else if (key == GLFW_KEY_RIGHT)
    {
      world->set_camera_delta_yaw(1.0F);
    }
  }
  else if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_LEFT_BRACKET || key == GLFW_KEY_RIGHT_BRACKET)
    {
      world->set_camera_delta_roll(0.0F);
    }
    else if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN)
    {
      world->set_camera_delta_pitch(0.0F);
    }
    else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)
    {
      world->set_camera_delta_yaw(0.0F);
    }
  }
}

int main()
{
  if (!glfwInit())
  {
    return -1;
  }

  GLFWwindow* window{glfwCreateWindow(512, 512, "Block Game", nullptr, nullptr)};
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

#if _DEBUG
  std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << std::endl;
#endif

  double time{0.0};
  double new_time;
  double delta;

  int width;
  int height;

  world = new block_game::World;

  glfwSetKeyCallback(window, KeyCallback);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    new_time = glfwGetTime();
    delta = new_time - time;
    time = new_time;
    world->Update(delta);

    glfwGetFramebufferSize(window, &width, &height);
    world->Display(width, height);
    glfwSwapBuffers(window);
  }

  delete world;

  glfwDestroyWindow(window);
  glfwTerminate();
}
