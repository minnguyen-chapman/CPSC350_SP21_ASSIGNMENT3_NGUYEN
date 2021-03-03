#ifndef GAME_H_
#define GAME_H_
#include "GameMap.h"
#include <string>
class Game{
public:
  Game(int o);
  Game(std::string f);
  ~Game() = default;
  void start();
  void setGameMap(GameMap* g);


private:
  GameMap* gameMap;
  int count = 0;
  int option = -1;
  std::string outFile;

};
#endif
