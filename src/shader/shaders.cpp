#include "shader/shaders.h"

#include <string>

namespace block_game
{
  const std::string program_vert{
#include "shader/program.vert.txt"
  };

  const std::string program_frag{
#include "shader/program.frag.txt"
  };
}
