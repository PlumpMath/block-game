#ifndef BLOCK_GAME_GAME_GAME_H_
#define BLOCK_GAME_GAME_GAME_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "block_game/game/world.h"
#include "block_game/general/camera.h"
#include "block_game/general/vector.h"

namespace block_game {
class Game {
public:
  Game(GLFWwindow* window);

  void Loop();

  void CursorPosCallback(double xpos, double ypos);
  void KeyCallback(int key, int scancode, int action, int mods);

private:
  GLFWwindow* window_;
  World world_;

  Vector<2> previous_cursor_position_;
};
}

#endif
