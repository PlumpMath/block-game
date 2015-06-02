#include <cassert>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"
#include "general/camera.h"
#include "general/vector.h"

block_game::Vector<2> previous_cursor_position;

block_game::World* world;

void CursorPosCallback(GLFWwindow* const window, const double xpos, const double ypos) {
  assert(world != nullptr);

  if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
    block_game::Camera& camera{world->GetCamera()};
    camera.SetYaw(static_cast<float>(camera.GetYaw() + 0.001F * (xpos - previous_cursor_position[0])));
    camera.SetPitch(static_cast<float>(camera.GetPitch() + 0.001F * (ypos - previous_cursor_position[1])));
  }

  previous_cursor_position[0] = static_cast<float>(xpos);
  previous_cursor_position[1] = static_cast<float>(ypos);
}

void KeyCallback(GLFWwindow* const window, const int key, const int scancode, const int action, const int mods) {
  assert(world != nullptr);

  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetInputMode(
        window,
        GLFW_CURSOR,
        glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
      );
    }
    if (key == GLFW_KEY_LEFT_CONTROL) {
      world->SetCameraDeltaVertical(-10.0F);
    } else if (key == GLFW_KEY_SPACE) {
      world->SetCameraDeltaVertical(10.0F);
    } else if (key == GLFW_KEY_W) {
      world->SetCameraDeltaForward(10.0F);
    } else if (key == GLFW_KEY_S) {
      world->SetCameraDeltaForward(-10.0F);
    } else if (key == GLFW_KEY_A) {
      world->SetCameraDeltaStrafe(-10.0F);
    } else if (key == GLFW_KEY_D) {
      world->SetCameraDeltaStrafe(10.0F);
    } else if (key == GLFW_KEY_LEFT_BRACKET) {
      world->SetCameraDeltaRoll(1.0F);
    } else if (key == GLFW_KEY_RIGHT_BRACKET) {
      world->SetCameraDeltaRoll(-1.0F);
    }
  } else if (action == GLFW_RELEASE) {
    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_SPACE) {
      world->SetCameraDeltaVertical(0.0F);
    } else if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
      world->SetCameraDeltaForward(0.0F);
    } else if (key == GLFW_KEY_A || key == GLFW_KEY_D) {
      world->SetCameraDeltaStrafe(0.0F);
    } else if (key == GLFW_KEY_LEFT_BRACKET || key == GLFW_KEY_RIGHT_BRACKET) {
      world->SetCameraDeltaRoll(0.0F);
    }
  }
}

int main() {
  if (!glfwInit()) {
    return EXIT_FAILURE;
  }
  GLFWwindow* const window{glfwCreateWindow(512, 512, "Block Game 0.3.0", nullptr, nullptr)};
  if (window == nullptr) {
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);
  gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

  std::clog << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::clog << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::clog << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::clog << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::clog << std::endl;

  world = new block_game::World;
  glfwSetCursorPosCallback(window, CursorPosCallback);
  glfwSetKeyCallback(window, KeyCallback);
  double previous_time{glfwGetTime()};

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    const double current_time{glfwGetTime()};
    const double delta_seconds{current_time - previous_time};
    previous_time = current_time;
    world->Update(delta_seconds);

    int screen_width;
    int screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    world->Display(screen_width, screen_height);
    glfwSwapBuffers(window);
  }

  delete world;
  glfwTerminate();
  return EXIT_SUCCESS;
}
