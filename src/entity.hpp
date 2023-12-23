#pragma once

#include <ostream>
#include <string>

namespace nd {
namespace init_tracker {
class Entity {
private:
  std::string m_Name;
  float_t m_Initiative;
  std::size_t m_FirstRound;

public:
  Entity(std::string const &name, float_t initiative);
  Entity(std::string const &name, float_t initiative, std::size_t firstRound);

  std::string const &getName() const;
  float_t getInitiative() const;
  std::size_t getFirstRound() const;

  bool Equals(Entity const &other) const;
};

std::ostream &operator<<(std::ostream &os, Entity const &entity);
bool operator==(Entity const &left, Entity const &right);
} // namespace init_tracker
} // namespace nd
