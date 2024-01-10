#include <algorithm> // std::find()
#include <iostream>  // std::cin, std::cout
#include <ostream>   // std::ostream, std::endl
#include <string>    // std::string, std::getline(), std::begin(), std::end()
#include <utility>   // std::move()
#include <vector>    // std::vector
#include <optional>  // std::optional

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
  double initiative;
  while (true) {
    std::cout << "New entity:\nName: ";
    std::cin >> str;
    std::cout << "Initiative: ";
    std::cin >> initiative;
    Entity entity{str, initiative};
    entities.push_back(entity);
    std::cout << "added entity { " << entity << " }\n\nAdd another entity? ";
    std::getline(std::cin, str);
    // need to read line from std::cin again to prevent automatic continuation
    // not really sure why though
    if (str == "")
    {
      std::getline(std::cin, str);
    }
    std::cout << "\n";
    if (std::find(std::begin(str), std::end(str), 'y') == std::end(str) &&
        std::find(std::begin(str), std::end(str), 'Y') == std::end(str)) {
      break;
    }
  }

  Encounter encounter{std::move(entities)};

  std::optional<Encounter::StepResult_t> stepResult{};
  do {
    printRoundHeader(std::cout, encounter.getCurrentRound());
    for (size_t i = 0; i < encounter.getEntities().size(); ++i) {
      std::cout << (i == encounter.getCurrentEntityIndex() ? "> " : "  ")
                << encounter.getEntities()[i] << "\n";
    }
    std::cout << "\n";
    std::getline(std::cin, str);
    stepResult = encounter.next();
  } while (stepResult.has_value() &&
           stepResult.value() != Encounter::StepResult_t::Finished &&
           std::find(std::begin(str), std::end(str), 'q') == std::end(str) &&
           std::find(std::begin(str), std::end(str), 'Q') == std::end(str));
  return 0;
}
