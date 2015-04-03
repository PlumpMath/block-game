#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include "general/color_3f.h"
#include "general/vector_3f.h"
#include "opengl/vertex_buffer.h"
#include "opengl/index_buffer.h"

namespace block_game
{
  class Program;

  class Block
  {
  public:
    Block(const float, const Color3F&);

    float radius() const;
    const Color3F& color() const;
    const Vector3F& position() const;
    const Vector3F& rotation() const;

    Vector3F& position();
    Vector3F& rotation();

    void Update(const double);
    void Draw(Program&) const;

  private:
    static const Vector3F vertices_[][2];
    static const unsigned char indices_[];

    const float radius_;
    const Color3F color_;
    Vector3F position_;
    Vector3F rotation_;

    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
  };
}

#endif
