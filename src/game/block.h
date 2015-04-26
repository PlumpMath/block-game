#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include "general/color_3f.h"
#include "general/vector_3f.h"
#include "opengl/index_buffer.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  class Program;

  class Block
  {
  public:
    Block(const Block*, const float, const Vector3F&);

    const Block* parent() const;
    float radius() const;
    const Vector3F& position() const;
    bool is_leaf() const;

    const Block* Child(const int, const int, const int) const;

    const Color3F& color() const;
    Color3F& color();

    void Draw(Program&) const;

  private:
    static const Vector3F vertices_[][2];
    static const unsigned char indices_[];

    const Block* parent_;
    const float radius_;
    const Vector3F position_;
    bool is_leaf_;

    Block* children[2][2][2];

    Color3F color_;
    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
  };
}

#endif
