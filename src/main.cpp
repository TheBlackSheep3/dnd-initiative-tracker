#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "cmake_variables.hpp"
#include "entity.hpp"

using namespace nd::init_tracker;

int main(int argc, char *argv[]) {
  std::cout << argv[0] << " version " << VERSION << std::endl;
  std::vector<Entity> skeletons;
  skeletons.reserve(5);
  char buffer[16];
  std::string str;
  for (int i = 0; i < 5; ++i) {
    snprintf(buffer, 9, "Skelly %d", i);
    str = std::string{buffer};
    Entity s{str, (float_t)i};
    skeletons.push_back(s);
  }

  std::cout << "sizeof(Entity): " << sizeof(Entity) << "\n";

  std::cout << "Skeletons:\n";
  for (int i = 0; i < 5; ++i) {
    std::cout << "  " << skeletons[i] << "\n";
  }
  return 0;
}
