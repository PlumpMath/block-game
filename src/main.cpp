#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"
#include "general/camera.h"
#include "general/vector_2f.h"

#if _DEBUG
#include <iostream>
#endif

block_game::Vector2F previous_cursor_pos;

block_game::World* world;

void CursorPosCallback(GLFWwindow* window, double x_pos, double y_pos)
{
  if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
  {
    block_game::Camera& camera{world->camera()};
    camera.set_yaw(camera.yaw() + 0.001F * (((float) x_pos) - previous_cursor_pos.x));
    camera.set_pitch(camera.pitch() + 0.001F * (((float) y_pos) - previous_cursor_pos.y));
  }

  previous_cursor_pos.x = x_pos;
  previous_cursor_pos.y = y_pos;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_ESCAPE)
    {
      glfwSetInputMode(window, GLFW_CURSOR,
        glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
    if (key == GLFW_KEY_MINUS)
    {
      world->set_camera_delta_vertical(-1.0F);
    }
    else if (key == GLFW_KEY_EQUAL)
    {
      world->set_camera_delta_vertical(1.0F);
    }
    else if (key == GLFW_KEY_W)
    {
      world->set_camera_delta_forward(1.0F);
    }
    else if (key == GLFW_KEY_S)
    {
      world->set_camera_delta_forward(-1.0F);
    }
    else if (key == GLFW_KEY_A)
    {
      world->set_camera_delta_strafe(-1.0F);
    }
    else if (key == GLFW_KEY_D)
    {
      world->set_camera_delta_strafe(1.0F);
    }
    else if (key == GLFW_KEY_LEFT_BRACKET)
    {
      world->set_camera_delta_roll(1.0F);
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET)
    {
      world->set_camera_delta_roll(-1.0F);
    }
  }
  else if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_MINUS || key == GLFW_KEY_EQUAL)
    {
      world->set_camera_delta_vertical(0.0F);
    }
    else if (key == GLFW_KEY_W || key == GLFW_KEY_S)
    {
      world->set_camera_delta_forward(0.0F);
    }
    else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
    {
      world->set_camera_delta_strafe(0.0F);
    }
    else if (key == GLFW_KEY_LEFT_BRACKET || key == GLFW_KEY_RIGHT_BRACKET)
    {
      world->set_camera_delta_roll(0.0F);
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
  glfwSetCursorPosCallback(window, CursorPosCallback);

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
