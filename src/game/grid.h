#ifndef BLOCK_GAME_GAME_GRID_H_
#define BLOCK_GAME_GAME_GRID_H_

#include <json/json.h>

#include "game/block.h"
#include "general/vector.h"
#include "opengl/buffer.h"

namespace block_game
{
class Program;

class Grid
{
public:
  Grid(float radius);
  Grid(const Json::Value& value);

  Vector<3> GetPosition() const;
  Vector<3> GetRotation() const;

  void SetPosition(const Vector<3>& position);
  void SetRotation(const Vector<3>& rotation);

  const Block& GetRoot() const;
  Block& GetRoot();

  void Update(double delta);
  void RebuildDraw();
  void Draw(Program& program);

private:
  Vector<3> position_;
  Vector<3> rotation_;
  Block root_;

  Buffer vertex_buffer_;
  Buffer index_buffer_;
};
}

#endif
