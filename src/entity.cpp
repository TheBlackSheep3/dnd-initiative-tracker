#include "entity.hpp"
#include <cstdint>
#include <ostream>

namespace nd {
namespace init_tracker {
Entity::Entity(std::string const &name, float initiative)
    : Entity{name, initiative, 1} {}

Entity::Entity(std::string const &name, float initiative,
               unsigned int firstRound)
    : m_Name{name}, m_Initiative{initiative} {
  if (firstRound > 0) {
    m_FirstRound = firstRound;
  } else {
    m_FirstRound = 1;
  }
}

std::string const &Entity::getName() const { return m_Name; }
float_t Entity::getInitiative() const { return m_Initiative; }
uint32_t Entity::getFirstRound() const { return m_FirstRound; }

std::ostream &operator<<(std::ostream &os, Entity const &entity) {
  return os << entity.getName() << " (" << entity.getInitiative() << ")";
}
} // namespace init_tracker
} // namespace nd
