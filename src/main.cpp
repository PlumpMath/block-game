#include "freeglut/glut.h"

#include "game/world.h"

block_game::World world;

void Display()
{
  world.Display();
}

void StartTimer();

void Timer(const int value)
{
  StartTimer();
  world.Update();
}

void StartTimer()
{
  glutTimerFunc(1000 / 60, Timer, 0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutCreateWindow("BlockGame");
  glutDisplayFunc(Display);
  StartTimer();
  glutMainLoop();
}
