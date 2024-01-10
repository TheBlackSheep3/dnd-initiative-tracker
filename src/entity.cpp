#include <cstddef>
#include <iomanip>
#include <ios>
#include <ostream>

#include "entity.hpp"

namespace nd {
namespace init_tracker {
Entity::Entity(std::string const &name, double initiative)
    : Entity{name, initiative, 1} {}

Entity::Entity(std::string const &name, double initiative,
               std::size_t firstRound)
    : m_Name{name}, m_Initiative{initiative} {
  if (firstRound > 0) {
    m_FirstRound = firstRound;
  } else {
    m_FirstRound = 1;
  }
}

std::string const &Entity::getName() const { return m_Name; }
double Entity::getInitiative() const { return m_Initiative; }
std::size_t Entity::getFirstRound() const { return m_FirstRound; }

bool Entity::Equals(Entity const &other) const {
  if (m_FirstRound != other.m_FirstRound) {
    return false;
  }
  if (m_Initiative != other.m_Initiative) {
    return false;
  }
  if (m_Name != other.m_Name) {
    return false;
  }
  return true;
}

std::ostream &operator<<(std::ostream &os, Entity const &entity) {
  return os << entity.getName() << " (" << std::fixed << std::setprecision(2)
            << entity.getInitiative() << ")";
}
bool operator==(Entity const &left, Entity const &right) {
  return left.Equals(right);
}
bool operator!=(Entity const &left, Entity const &right) {
  return !left.Equals(right);
}
} // namespace init_tracker
} // namespace nd
