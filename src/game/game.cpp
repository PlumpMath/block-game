#include "game/game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/world.h"
#include "general/camera.h"
#include "general/vector.h"

namespace block_game {
Game::Game(GLFWwindow* const window) :
  window_{window}
{
}

void Game::Loop() {
  double previous_time{glfwGetTime()};
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();

    const double current_time{glfwGetTime()};
    const double delta_seconds{current_time - previous_time};
    previous_time = current_time;
    world_.Update(delta_seconds);

    int screen_width;
    int screen_height;
    glfwGetFramebufferSize(window_, &screen_width, &screen_height);
    world_.Display(screen_width, screen_height);
    glfwSwapBuffers(window_);
  }
}

void Game::CursorPosCallback(const double xpos, const double ypos) {
  if (glfwGetInputMode(window_, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
    block_game::Camera& camera{world_.GetCamera()};
    camera.SetYaw(static_cast<float>(camera.GetYaw() + 0.001F * (xpos - previous_cursor_position_[0])));
    camera.SetPitch(static_cast<float>(camera.GetPitch() + 0.001F * (ypos - previous_cursor_position_[1])));
  }

  previous_cursor_position_[0] = static_cast<float>(xpos);
  previous_cursor_position_[1] = static_cast<float>(ypos);
}

void Game::KeyCallback(const int key, const int scancode, const int action, const int mods) {
  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetInputMode(
        window_,
        GLFW_CURSOR,
        glfwGetInputMode(window_, GLFW_CURSOR) == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
        );
    }
    if (key == GLFW_KEY_LEFT_CONTROL) {
      world_.SetCameraDeltaVertical(-10.0F);
    } else if (key == GLFW_KEY_SPACE) {
      world_.SetCameraDeltaVertical(10.0F);
    } else if (key == GLFW_KEY_W) {
      world_.SetCameraDeltaForward(10.0F);
    } else if (key == GLFW_KEY_S) {
      world_.SetCameraDeltaForward(-10.0F);
    } else if (key == GLFW_KEY_A) {
      world_.SetCameraDeltaStrafe(-10.0F);
    } else if (key == GLFW_KEY_D) {
      world_.SetCameraDeltaStrafe(10.0F);
    } else if (key == GLFW_KEY_LEFT_BRACKET) {
      world_.SetCameraDeltaRoll(1.0F);
    } else if (key == GLFW_KEY_RIGHT_BRACKET) {
      world_.SetCameraDeltaRoll(-1.0F);
    }
  } else if (action == GLFW_RELEASE) {
    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_SPACE) {
      world_.SetCameraDeltaVertical(0.0F);
    } else if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
      world_.SetCameraDeltaForward(0.0F);
    } else if (key == GLFW_KEY_A || key == GLFW_KEY_D) {
      world_.SetCameraDeltaStrafe(0.0F);
    } else if (key == GLFW_KEY_LEFT_BRACKET || key == GLFW_KEY_RIGHT_BRACKET) {
      world_.SetCameraDeltaRoll(0.0F);
    }
  }
}
}
