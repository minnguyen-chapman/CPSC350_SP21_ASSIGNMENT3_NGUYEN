#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include <string>
class GameMap{
public:
  GameMap() = default;
  GameMap(std::string fileName,int m);
  GameMap(int x, int y, float pop, int m);
  ~GameMap();
  float getAverageNeighbors(int x, int y);
  void advanceMap();
  bool isEmpty();
  void updateMap();
  void printMap();
  std::string toString();
  bool isStable();
private:
  char** map1;
  char** map2;
  char** map3;
  int round = 0;
  int getNeighbors(char** m, int x, int y);
  int w;
  int h;
  float** neighborMap;
  int mode;
};
#endif
