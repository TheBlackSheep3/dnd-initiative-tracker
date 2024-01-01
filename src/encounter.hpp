#pragma once

#include <cstddef>
#include <vector>

#include "entity.hpp"

namespace nd {
namespace init_tracker {
class Encounter {
private:
  std::vector<Entity> m_Entities;
  std::size_t m_Round;
  std::size_t m_MaxRounds;
  std::size_t m_EntityIndex;

  inline void sortEntities(std::vector<Entity>& entities);

public:
  Encounter(std::vector<Entity> &&entities);
  Encounter(std::vector<Entity> &&entities, std::size_t round,
            std::size_t maxRounds, std::size_t entityIndex);

  enum StepResult_t {
    Finished,
    NextEntity,
    NextRound,
  };

  StepResult_t next();
  bool addEntity(Entity const &entity);
  bool removeEntity(std::size_t entityIndex);

  std::vector<Entity> const &getEntities() const;
  std::size_t getCurrentRound() const;
  std::size_t getMaxRounds() const;
  std::size_t getCurrentEntityIndex() const;
};
} // namespace init_tracker
} // namespace nd
