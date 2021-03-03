#include "GameMap.h"
#include <string>
#include <fstream>
#include <iostream>
// Generates gameMap from file and set mode
GameMap::GameMap(std::string fileName,int m){
  mode = m;
  std::string line;
  std::ifstream read_file(fileName);
  int lineNo = 0;
  while(std::getline(read_file,line)) {
    if (lineNo == 0) {
      h = std::stoi (line);
    } else if (lineNo == 1) {
      w = std::stoi (line);

      // dynamically initializes 2D arrays
      map1 = new char* [h];
      for(int i = 0; i < h; ++i) {
        map1[i] = new char[w];
      }
      map2 = new char* [h];
      for(int i = 0; i < h; ++i) {
        map2[i] = new char[w];
      }
      map3 = new char* [h];
      for(int i = 0; i < h; ++i) {
        map3[i] = new char[w];
      }
      neighborMap = new float* [h];
      for(int i = 0; i < h; ++i) {
        neighborMap[i] = new float[w];
      }
    } else {
      for (int i = 0; i < w; i++) {
        // do lineNo - 2 because the first row doesn't occur until lineNo = 2
        map1[lineNo - 2][i] = line[i];
      }
    }
    lineNo++;
  }
  read_file.close();
}

// Generates gameMap from population density and set mode
GameMap::GameMap(int x, int y, float pop, int m){
  mode = m;
  w = x;
  h = y;
  map1 = new char* [h];
  for(int i = 0; i < h; i++) {
    map1[i] = new char[w];
  }
  map2 = new char* [h];
  for(int i = 0; i < h; i++) {
    map2[i] = new char[w];
  }
  map3 = new char* [h];
  for(int i = 0; i < h; i++) {
    map3[i] = new char[w];
  }
  neighborMap = new float* [h];
  for(int i = 0; i < h; ++i) {
    neighborMap[i] = new float[w];
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if((float) rand()/RAND_MAX <= pop) {
        map1[i][j] = 'X';
      } else {
        map1[i][j] = '-';
      }
    }
  }
}

GameMap::~GameMap(){
  for (int i = 0; i < h; i++) {
   delete[] map1[i];
  }
  delete[] map1;

  for (int i = 0; i < h; i++) {
   delete[] map2[i];
  }
  delete[] map2;

  for (int i = 0; i < h; i++) {
   delete[] map3[i];
  }
  delete[] map3;

  for (int i = 0; i < h; i++) {
   delete[] neighborMap[i];
  }
  delete[] neighborMap;
}

// update map3 and map2 to be correct values
void GameMap::advanceMap(){
  if (round > 0) {
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        map3[i][j] = map2[i][j];
      }
    }
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      map2[i][j] = map1[i][j];
    }
  }
}

// depending on round number, returns avg neighbor count for 3 generations
float GameMap::getAverageNeighbors(int x, int y){
  int count = 0;
  count += getNeighbors(map1,x,y);
  if (round == 0){
    return count;
  }
  count += getNeighbors(map2,x,y);
  if (round == 1) {
    return count / 2.0f;
  }
  count += getNeighbors(map3,x,y);
  return count / 3.0f;
}

// returns number of neighbors given the map array
int GameMap::getNeighbors(char** m, int x, int y){
  // deal with coordinate arithmetic now to make it easier to deal with modes
  int count = 0;
  int xSub1 = x - 1;
  int xAdd1 = x + 1;
  int ySub1 = y - 1;
  int yAdd1 = y + 1;

  // if donut mode, modulo accomplishes the wrap-around effect
  if (mode == 1) {
      xSub1 %= w;
      xAdd1 %= w;
      ySub1 %= h;
      ySub1 %= h;
  } else if (mode == 2) { // if mirror mode, constrain to the bounds of map
      xSub1 = std::max(0,xSub1);
      xAdd1 = std::min(w-1,xAdd1);
      ySub1 = std::max(0,ySub1);
      yAdd1 = std::min(h-1,yAdd1);
  }
  // bounds checking in case of classic mode
  if (ySub1 != -1 && xSub1 != -1 && m[ySub1][xSub1] == 'X') {
    ++count;
  }
  if (xSub1 != -1 && m[y][xSub1] == 'X') {
    ++count;
  }
  if (xSub1 != -1 && yAdd1 != h && m[yAdd1][xSub1] == 'X') {
    ++count;
  }
  if (ySub1 != -1 && m[ySub1][x] == 'X') {
    ++count;
  }
  if (yAdd1 != h && m[yAdd1][x] == 'X') {
    ++count;
  }
  if (xAdd1 != w && ySub1 != -1 && m[ySub1][xAdd1] == 'X') {
    ++count;
  }
  if (xAdd1 != w && m[y][xAdd1] == 'X') {
    ++count;
  }
  if (yAdd1 != h && xAdd1 != w && m[yAdd1][xAdd1] == 'X') {
    ++count;
  }
  return count;
}

bool GameMap::isEmpty(){
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (map1[i][j] == 'X') {
        return false;
      }
    }
  }
  return true;
}

// map is considered stable if all 3 generations is the same
bool GameMap::isStable(){
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (map1[i][j] != map2[i][j] || map1[i][j] != map3[i][j]) {
        return false;
      }
    }
  }
  return true;
}

// compute neighbors, advances map, then updates current generation according to assignment rules
void GameMap::updateMap(){
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      neighborMap[i][j] = getAverageNeighbors(j,i);
    }
  }
  advanceMap();
  round++;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (neighborMap[i][j] < 1.5f) {
        map1[i][j] = '-';
      } else if (neighborMap[i][j] <= 2.5f) {
        continue;
      } else if (neighborMap[i][j] <= 3.5f) {
        map1[i][j] = 'X';
      } else {
        map1[i][j] = '-';
      }
    }
  }
}

void GameMap::printMap(){
  std::cout << toString();
}

std::string GameMap::toString(){
  std::string mapString = "";
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      mapString += map1[i][j];
    }
    mapString += "\n";
  }
  return mapString;
}
