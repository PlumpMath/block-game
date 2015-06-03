#include <cassert>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/game.h"

namespace {
block_game::Game* game;

void CursorPosCallback(GLFWwindow* const window, const double xpos, const double ypos) {
  assert(game != nullptr);

  game->CursorPosCallback(xpos, ypos);
}

void KeyCallback(GLFWwindow* const window, const int key, const int scancode, const int action, const int mods) {
  assert(game != nullptr);

  game->KeyCallback(key, scancode, action, mods);
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

  game = new block_game::Game{window};
  glfwSetCursorPosCallback(window, CursorPosCallback);
  glfwSetKeyCallback(window, KeyCallback);

  game->Loop();

  delete game;
  glfwTerminate();
  return EXIT_SUCCESS;
}
