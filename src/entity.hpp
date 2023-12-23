#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace nd {
namespace init_tracker {
class Entity {
private:
  std::string m_Name;
  float_t m_Initiative;
  uint32_t m_FirstRound;

public:
  Entity(std::string const &name, float_t initiative);
  Entity(std::string const &name, float_t initiative, uint32_t firstRound);

  std::string const &getName() const;
  float_t getInitiative() const;
  unsigned int getFirstRound() const;
};

std::ostream &operator<<(std::ostream &os, Entity const &entity);
} // namespace init_tracker
} // namespace nd
