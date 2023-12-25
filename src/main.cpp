#include <algorithm>
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
  std::vector<Entity> entities{};
  std::string str{};
  float_t initiative;
  while (true) {
    std::cout << "New entity:\nName: ";
    std::cin >> str;
    std::cout << "Initiative: ";
    std::cin >> initiative;
    Entity entity{str, initiative};
    entities.push_back(entity);
    std::cout << "added entity { " << entity << " }\n\nAdd another entity? ";
    std::cin >> str;
    if (std::find(str.begin(), str.end(), 'y') == str.end() &&
        std::find(str.begin(), str.end(), 'Y') == str.end()) {
      break;
    }
  }
  Encounter encounter{std::move(entities), 1, 3, 0};

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
