#include "game/game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"
#include "general/camera.h"
#include "general/vector.h"

namespace {
const float kMouseSensitivity{0.001F};
}

namespace block_game {
Game::Game(GLFWwindow* const window) :
  window_{window}
{}

void Game::Loop() {
  double previous_time{glfwGetTime()};
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();

    const double current_time{glfwGetTime()};
    const double delta_seconds{current_time - previous_time};
    world_.Update(delta_seconds);
    previous_time = current_time;

    int screen_width;
    int screen_height;
    glfwGetFramebufferSize(window_, &screen_width, &screen_height);
    world_.Display(screen_width, screen_height);
    glfwSwapBuffers(window_);
  }
}

void Game::CursorPosCallback(const double xpos, const double ypos) {
  const Vector<2> current_cursor_position{static_cast<float>(xpos), static_cast<float>(ypos)};
  const Vector<2> delta_cursor_position{current_cursor_position - previous_cursor_position_};
  if (glfwGetInputMode(window_, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
    block_game::Camera& camera{world_.GetCamera()};
    camera.SetYaw(static_cast<float>(camera.GetYaw() + kMouseSensitivity * delta_cursor_position[0]));
    camera.SetPitch(static_cast<float>(camera.GetPitch() + kMouseSensitivity * delta_cursor_position[1]));
  }
  previous_cursor_position_ = current_cursor_position;
}

void Game::KeyCallback(const int key, const int scancode, const int action, const int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
        // toggle cursor input mode
        glfwSetInputMode(
          window_,
          GLFW_CURSOR,
          glfwGetInputMode(window_, GLFW_CURSOR) == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
        );
        break;
      case GLFW_KEY_LEFT_CONTROL:
        world_.SetCameraVerticalSpeed(-10.0F);
        break;
      case GLFW_KEY_SPACE:
        world_.SetCameraVerticalSpeed(10.0F);
        break;
      case GLFW_KEY_W:
        world_.SetCameraForwardSpeed(10.0F);
        break;
      case GLFW_KEY_S:
        world_.SetCameraForwardSpeed(-10.0F);
        break;
      case GLFW_KEY_A:
        world_.SetCameraStrafeSpeed(-10.0F);
        break;
      case GLFW_KEY_D:
        world_.SetCameraStrafeSpeed(10.0F);
        break;
      case GLFW_KEY_LEFT_BRACKET:
        world_.SetCameraRollSpeed(1.0F);
        break;
      case GLFW_KEY_RIGHT_BRACKET:
        world_.SetCameraRollSpeed(-1.0F);
        break;
      default:
        break;
    }
  } else if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_LEFT_CONTROL:
      case GLFW_KEY_SPACE:
        world_.SetCameraVerticalSpeed(0.0F);
        break;
      case GLFW_KEY_W:
      case GLFW_KEY_S:
        world_.SetCameraForwardSpeed(0.0F);
        break;
      case GLFW_KEY_A:
      case GLFW_KEY_D:
        world_.SetCameraStrafeSpeed(0.0F);
        break;
      case GLFW_KEY_LEFT_BRACKET:
      case GLFW_KEY_RIGHT_BRACKET:
        world_.SetCameraRollSpeed(0.0F);
        break;
      default:
        break;
    }
  }
}
}
