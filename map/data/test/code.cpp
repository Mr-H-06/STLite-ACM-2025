#include "map.hpp"
#include <iostream>

sjtu::map<int, std::string> map;

int main() {
  for (int i = 0; i < 3; ++i) {
    map.insert(sjtu::pair<int, std::string>(i, ""));
  }
  for (int i = 1; i < 3; ++i) {
    std::cout << map.find(i)->first << '\n';
    map.erase(map.find(i));
  }/*
  for (int i = 0; i < 11; ++i){
    std::cout << map.count(i) << '\n';
  }*/
}
