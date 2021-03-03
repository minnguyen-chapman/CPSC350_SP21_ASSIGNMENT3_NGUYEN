#include "Game.h"
#include "GameMap.h"
#include <string>
#include <iostream>

int main(int argc, char * argv[])
{
  std::cout << "Enter the corresponding number for the map that you want: " << std::endl;
  std::cout << "0. Provide a map file" << std::endl << "1. Generate one" << std::endl;
  std::string mapOption;
  std::getline(std::cin,mapOption);
  if (mapOption == "0") {
    std::cout << "Please enter the map file: " << std::endl;
    std::string mapFile;
    std::getline(std::cin,mapFile);
    std::cout << "Enter the corresponding number for the simulation mode you want: " << std::endl;
    std::cout << "0. Classic" << std::endl << "1. Donut" << std::endl << "2. Mirror" << std::endl;
    std::string modeStr;
    std::getline(std::cin,modeStr);
    int mode = std::stoi(modeStr);
    std::cout << "Enter the corresponding number for the display mode: " << std::endl;
    std::cout << "0. Brief pause" << std::endl << "1. Advance on user input" << std::endl << "2. Save to file" << std::endl;
    std::string optionStr;
    std::getline(std::cin,optionStr);
    int option = std::stoi(optionStr);
    if (option == 2) {
      std::cout << "Enter file name: " << std::endl;
      std::string fileName;
      std::getline(std::cin,fileName);
      Game* game = new Game(fileName);
      GameMap* gameMap = new GameMap(mapFile,mode);
      game->setGameMap(gameMap);
      game->start();
      delete game;
      delete gameMap;
    } else {
      Game* game = new Game(option);
      GameMap* gameMap = new GameMap(mapFile,mode);
      game->setGameMap(gameMap);
      game->start();
      delete game;
      delete gameMap;
    }
  } else {
    std::cout << "Enter the height: " << std::endl;
    std::string hString;
    std::getline(std::cin,hString);
    int h = std::stoi(hString);
    std::cout << "Enter the width: " << std::endl;
    std::string wString;
    std::getline(std::cin,wString);
    int w = std::stoi(wString);
    std::cout << "Enter the population(e.g. 0.75): " << std::endl;
    std::string popString;
    std::getline(std::cin,popString);
    float population = std::stof(popString);
    std::cout << "Enter the corresponding number for the simulation mode you want: " << std::endl;
    std::cout << "0. Classic" << std::endl << "1. Donut" << std::endl << "2. Mirror" << std::endl;
    std::string modeStr;
    std::getline(std::cin,modeStr);
    int mode = std::stoi(modeStr);
    std::cout << "Enter the corresponding number for the display mode: " << std::endl;
    std::cout << "0. Brief pause" << std::endl << "1. Advance on user input" << std::endl << "2. Save to file" << std::endl;
    std::string optionStr;
    std::getline(std::cin,optionStr);
    int option = std::stoi(optionStr);
    if (option == 2) {
      std::cout << "Enter file name: " << std::endl;
      std::string fileName;
      std::getline(std::cin,fileName);
      Game* game = new Game(fileName);
      GameMap* gameMap = new GameMap(w,h,population,mode);
      game->setGameMap(gameMap);
      game->start();
      delete game;
      delete gameMap;
    } else {
      Game* game = new Game(option);
      GameMap* gameMap = new GameMap(w,h,population,mode);
      game->setGameMap(gameMap);
      game->start();
      delete game;
      delete gameMap;
    }
  }
}
