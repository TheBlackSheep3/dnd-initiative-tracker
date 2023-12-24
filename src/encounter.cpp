#include <algorithm>
#include <exception>
#include <iterator>
#include <limits>
#include <vector>

#include "encounter.hpp"
#include "entity.hpp"

namespace nd {
namespace init_tracker {
Encounter::Encounter(std::vector<Entity> &&entities)
    : Encounter{std::move(entities), 1, std::numeric_limits<std::size_t>::max(),
                0} {}
Encounter::Encounter(std::vector<Entity> &&entities, std::size_t round,
                     std::size_t maxRounds, std::size_t entityIndex)
    : m_Entities{entities}, m_Round{round}, m_MaxRounds{maxRounds},
      m_EntityIndex{entityIndex} {}

Encounter::StepResult_t Encounter::next() {
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
    std::sort(copy.begin(), copy.end(),
              [](Entity const &left, Entity const &right) {
                return left.getInitiative() > right.getInitiative();
              });
    if (m_Entities.size() > 0) {
      bool found = false;
      std::size_t index = 0;
      for (auto entity : copy) {
        if (entity == m_Entities[m_EntityIndex]) {
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
    if (entityIndex >= m_EntityIndex && m_EntityIndex != 0) {
      m_EntityIndex -= 1;
    }
    std::vector<Entity> copy = m_Entities;
    copy.erase(std::next(copy.begin(), entityIndex),
               std::next(copy.begin(), entityIndex + 1));
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
