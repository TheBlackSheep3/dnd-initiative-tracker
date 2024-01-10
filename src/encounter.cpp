#include <algorithm> // std::sort()
#include <exception> // std::exception
#include <iterator>  // std::next()
#include <limits>    // std::numeric_limits
#include <utility>   // std::move()
#include <vector>    // std::vector, std::begin()

#include "encounter.hpp"
#include "entity.hpp"

namespace nd {
namespace init_tracker {
inline void Encounter::sortEntities(std::vector<Entity>& entities) const {
  std::sort(entities.begin(), entities.end(),
            [](Entity const &left, Entity const &right) {
              return left.getInitiative() > right.getInitiative();
            });
}

Encounter::Encounter()
    : Encounter{ std::vector<Entity>{} } {}
Encounter::Encounter(std::vector<Entity> &&entities)
    : Encounter{std::move(entities), 1, std::numeric_limits<std::size_t>::max(),
                0} {}
Encounter::Encounter(std::vector<Entity> &&entities, std::size_t round,
                     std::size_t maxRounds, std::size_t entityIndex)
    : m_Entities{std::move(entities)}, m_Round{round}, m_MaxRounds{maxRounds},
      m_EntityIndex{entityIndex} {
  sortEntities(m_Entities);
}

Encounter::StepResult_t Encounter::next() {
  if (m_Entities.empty()) {
    return Encounter::StepResult_t::Finished;
  }
  m_EntityIndex += 1;
  if (m_EntityIndex >= m_Entities.size()) {
    m_EntityIndex = 0;
    m_Round += 1;
    if (m_Round >= m_MaxRounds) {
      return Encounter::StepResult_t::Finished;
    } else {
      return Encounter::StepResult_t::NextRound;
    }
  } else {
    return Encounter::StepResult_t::NextEntity;
  }
}
bool Encounter::addEntity(Entity const &entity) {
  try {
    std::vector<Entity> copy = m_Entities;
    copy.push_back(entity);
    sortEntities(copy);
    if (!m_Entities.empty()) {
      bool found = false;
      std::size_t index = 0;
      for (Entity const& e : copy) {
        if (e == m_Entities[m_EntityIndex]) {
          found = true;
          break;
        }
        index += 1;
      }
      if (found) {
        m_Entities = std::move(copy);
        m_EntityIndex = index;
        return true;
      } else {
        return false;
      }
    } else {
      m_Entities = std::move(copy);
      return true;
    }
  } catch (std::exception) {
    return false;
  }
}
bool Encounter::removeEntity(std::size_t entityIndex) {
  if (entityIndex >= m_Entities.size()) {
    return false;
  }
  try {
    if (entityIndex < m_EntityIndex && m_EntityIndex != 0) {
      m_EntityIndex -= 1;
    }
    std::vector<Entity> copy = m_Entities;
    copy.erase(std::next(std::begin(copy), entityIndex),
               std::next(std::begin(copy), entityIndex + 1));
    m_Entities = std::move(copy);
    return true;
  } catch (std::exception) {
    return false;
  }
}

std::vector<Entity> const &Encounter::getEntities() const { return m_Entities; }
std::size_t Encounter::getCurrentRound() const { return m_Round; }
std::size_t Encounter::getMaxRounds() const { return m_MaxRounds; }
std::size_t Encounter::getCurrentEntityIndex() const { return m_EntityIndex; }
} // namespace init_tracker
} // namespace nd
