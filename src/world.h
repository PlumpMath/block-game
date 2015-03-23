#ifndef BLOCK_GAME_WORLD_H_
#define BLOCK_GAME_WORLD_H_

namespace block_game
{
  class World
  {
  public:
    World();

    void Update();
    void Display() const;

  private:
    float angle_;
  };
}

#endif
