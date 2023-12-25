#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "cmake_variables.hpp"
#include "encounter.hpp"
#include "entity.hpp"

using namespace nd::init_tracker;

void printRoundHeader(std::ostream &os, size_t round) {
  std::string s(20, '=');
  os << s << " Round " << round << " " << s << "\n";
}

int main(/* int argc, char *argv[] */) {
  std::cout << PROJECT_NAME << "\nby " << AUTHOR << "\nVersion " << VERSION
            << "\n"
            << std::endl;
  char buffer[16];
  std::vector<Entity> skeletons{};
  std::string str{};
  for (int i = 0; i < 5; ++i) {
    snprintf(buffer, 9, "Skelly %d", i);
    str = std::string{buffer};
    skeletons.push_back(Entity{str, static_cast<float_t>(i)});
  }
  Encounter encounter{std::move(skeletons), 1, 3, 0};

  std::cout << "sizeof(Entity): " << sizeof(Entity) << "\n";
  std::cout << "sizeof(Encounter): " << sizeof(Encounter) << "\n";

  std::optional<Encounter::StepResult_t> stepResult{};
  do {
    printRoundHeader(std::cout, encounter.getCurrentRound());
    for (size_t i = 0; i < encounter.getEntities().size(); ++i) {
      std::cout << (i == encounter.getCurrentEntityIndex() ? "> " : "  ")
                << encounter.getEntities()[i] << "\n";
    }
    std::cout << "\n";
    stepResult = encounter.next();
  } while (stepResult.has_value() &&
           stepResult.value() != Encounter::StepResult_t::Finished);
  return 0;
}
