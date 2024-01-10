#pragma once

#include <ostream>
#include <string>

namespace nd {
namespace init_tracker {
class Entity {
private:
  std::string m_Name;
  double m_Initiative;
  std::size_t m_FirstRound;

public:
  Entity(std::string const &name, double initiative);
  Entity(std::string const &name, double initiative, std::size_t firstRound);

  std::string const &getName() const;
  double getInitiative() const;
  std::size_t getFirstRound() const;

  bool Equals(Entity const &other) const;
};

std::ostream &operator<<(std::ostream &os, Entity const &entity);
bool operator==(Entity const &left, Entity const &right);
bool operator!=(Entity const &left, Entity const &right);
} // namespace init_tracker
} // namespace nd
