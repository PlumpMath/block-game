#include <cassert>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"
#include "general/camera.h"
#include "general/vector.h"

block_game::Vector<2> previous_cursor_pos;

block_game::World* world;

void CursorPosCallback(GLFWwindow* window, const double x_pos, const double y_pos)
{
  assert(world != nullptr);

  if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
  {
    block_game::Camera& camera{world->GetCamera()};
    camera.SetYaw(static_cast<float>(camera.GetYaw() + 0.001F * (x_pos - previous_cursor_pos[0])));
    camera.SetPitch(static_cast<float>(camera.GetPitch() + 0.001F * (y_pos - previous_cursor_pos[1])));
  }

  previous_cursor_pos[0] = static_cast<float>(x_pos);
  previous_cursor_pos[1] = static_cast<float>(y_pos);
}

void KeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
  assert(world != nullptr);

  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_ESCAPE)
    {
      glfwSetInputMode(window, GLFW_CURSOR,
        glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
    if (key == GLFW_KEY_LEFT_CONTROL)
    {
      world->SetCameraDeltaVertical(-10.0F);
    }
    else if (key == GLFW_KEY_SPACE)
    {
      world->SetCameraDeltaVertical(10.0F);
    }
    else if (key == GLFW_KEY_W)
    {
      world->SetCameraDeltaForward(10.0F);
    }
    else if (key == GLFW_KEY_S)
    {
      world->SetCameraDeltaForward(-10.0F);
    }
    else if (key == GLFW_KEY_A)
    {
      world->SetCameraDeltaStrafe(-10.0F);
    }
    else if (key == GLFW_KEY_D)
    {
      world->SetCameraDeltaStrafe(10.0F);
    }
    else if (key == GLFW_KEY_LEFT_BRACKET)
    {
      world->SetCameraDeltaRoll(1.0F);
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET)
    {
      world->SetCameraDeltaRoll(-1.0F);
    }
  }
  else if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_SPACE)
    {
      world->SetCameraDeltaVertical(0.0F);
    }
    else if (key == GLFW_KEY_W || key == GLFW_KEY_S)
    {
      world->SetCameraDeltaForward(0.0F);
    }
    else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
    {
      world->SetCameraDeltaStrafe(0.0F);
    }
    else if (key == GLFW_KEY_LEFT_BRACKET || key == GLFW_KEY_RIGHT_BRACKET)
    {
      world->SetCameraDeltaRoll(0.0F);
    }
  }
}

int main()
{
  if (!glfwInit())
  {
    return EXIT_FAILURE;
  }

  GLFWwindow* window{glfwCreateWindow(512, 512, "Block Game 0.2.1", nullptr, nullptr)};
  if (!window)
  {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  std::clog << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::clog << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::clog << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::clog << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::clog << std::endl;

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
  return EXIT_SUCCESS;
}
