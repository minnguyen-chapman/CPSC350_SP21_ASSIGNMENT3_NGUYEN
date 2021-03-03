#include "Game.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>

Game::Game(int o){
  option = o;
}

Game::Game(std::string f){
  outFile = f;
}

void Game::setGameMap(GameMap* g){
  gameMap = g;
}

// starts simulation
void Game::start(){
  std::ofstream write_file;
  if (option == -1) {
    write_file.open(outFile,std::ofstream::out);
  }
  // only progress simulation if the map is not empty and not stable
  while (! gameMap->isEmpty() && ! gameMap->isStable()) {
    if (option == 0) { // auto advances simulation every one second
      std::cout << count << std::endl;
      gameMap->printMap();
      usleep(1000000);
    } else if (option == 1) { // advances simulation with user input
      std::cout << count << std::endl;
      gameMap->printMap();
      do {
        std::cout << '\n' << "Press the Enter key to continue.";
      } while (std::cin.get() != '\n');
    } else { // writes simulation to file
      write_file << count << std::endl;
      write_file << gameMap->toString();
    }

    gameMap->updateMap();
    ++count;
  }
  if (option == -1) {
    write_file << count << std::endl;
    write_file << gameMap->toString();
    write_file.close();
  } else {
    std::cout << count << std::endl;
    gameMap->printMap();
  }
}
