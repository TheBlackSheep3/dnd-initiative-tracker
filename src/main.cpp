#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

#include "cmake_variables.hpp"
#include "encounter.hpp"
#include "entity.hpp"

using namespace nd::init_tracker;

void printRoundHeader(std::ostream &os, size_t round) {
  std::string s(20, '=');
  os << s << " Round 1 " << s << "\n";
}

int main(int argc, char *argv[]) {
  std::cout << argv[0] << " version " << VERSION << std::endl;
  char buffer[16];
  std::string str{};
  Encounter encounter{1, 3};
  for (int i = 0; i < 5; ++i) {
    snprintf(buffer, 9, "Skelly %d", i);
    str = std::string{buffer};
    Entity s{str, (float_t)i};
    encounter.addEntity(s);
  }

  std::cout << "sizeof(Entity): " << sizeof(Entity) << "\n";
  std::cout << "sizeof(Encounter): " << sizeof(Encounter) << "\n";

  std::optional<Encounter::StepResult_t> stepResult{};
  do {
    printRoundHeader(std::cout, encounter.getCurrentRound());
    std::cout << "\n";
    for (size_t i = 0; i < encounter.getEntities().size(); ++i) {
      std::cout << (i == encounter.getCurrentEntityIndex() ? "> " : "  ")
                << encounter.getEntities()[i] << "\n";
    }
    std::optional{encounter.next()};
  } while (stepResult.has_value() &&
           stepResult.value() != Encounter::StepResult_t::Finished);
  return 0;
}
