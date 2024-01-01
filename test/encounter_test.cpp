#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <vector>

#include "encounter.hpp"

namespace nd {
namespace init_tracker {
class EncounterTest : public testing::Test {
protected:
  Encounter empty_encounter;
  Encounter fresh_encounter;
  Encounter middle_encounter;
  Encounter finished_encounter;

  std::vector<Entity> const encounter_entities = {Entity{"Barbarian", 10.08F},
                                                  Entity{"Rogue", 18.16F},
                                                  Entity{"Wizard", 13.10F}};

  EncounterTest()
      : empty_encounter{std::vector<Entity>{}},
        fresh_encounter{std::vector<Entity>{}},
        middle_encounter{std::vector<Entity>{}},
        finished_encounter{std::vector<Entity>{}} {
    std::vector<Entity> entities = encounter_entities;
    fresh_encounter = Encounter{std::move(entities), /* round */ 1,
                                /* max rounds */ 5, /* current entity */ 0};
    entities = encounter_entities;
    middle_encounter = Encounter{std::move(entities), /* round */ 3,
                                 /* max rounds */ 5, /* current entity */ 1};
    entities = encounter_entities;
    finished_encounter = Encounter{std::move(entities), /* round */ 5,
                                   /* max rounds */ 5, /* current entity */ 2};
  }

  bool AreEntitiesSorted() const {
    auto initiative_compare = [](Entity const &left, Entity const &right) {
      return left.getInitiative() >= right.getInitiative();
    };
    if (!std::is_sorted(std::begin(empty_encounter.getEntities()),
                        std::end(empty_encounter.getEntities()),
                        initiative_compare)) {
      return false;
    } else if (!std::is_sorted(std::begin(fresh_encounter.getEntities()),
                               std::end(fresh_encounter.getEntities()),
                               initiative_compare)) {
      return false;
    } else if (!std::is_sorted(std::begin(middle_encounter.getEntities()),
                               std::end(middle_encounter.getEntities()),
                               initiative_compare)) {
      return false;
    } else if (!std::is_sorted(std::begin(finished_encounter.getEntities()),
                               std::end(finished_encounter.getEntities()),
                               initiative_compare)) {
      return false;
    } else {
      return true;
    }
  }
  void SetUp() override { ASSERT_TRUE(AreEntitiesSorted()); }
};

TEST_F(EncounterTest, NextTest) {
  EXPECT_EQ(Encounter::Finished, empty_encounter.next());
  EXPECT_EQ(Encounter::NextEntity, fresh_encounter.next());
  EXPECT_EQ(Encounter::NextEntity, middle_encounter.next());
  EXPECT_EQ(Encounter::NextRound, middle_encounter.next());
  EXPECT_EQ(Encounter::Finished, finished_encounter.next());
}
TEST_F(EncounterTest, AddEntityTest) {
  Entity boblin{"Boblin", 7.09};
  ASSERT_TRUE(empty_encounter.addEntity(boblin));
  ASSERT_EQ(1, empty_encounter.getEntities().size());
  EXPECT_EQ(boblin, empty_encounter.getEntities()[0]);
  EXPECT_EQ(0, empty_encounter.getCurrentEntityIndex());
  EXPECT_EQ(1, empty_encounter.getCurrentRound());
  EXPECT_EQ(std::numeric_limits<std::size_t>::max(),
            empty_encounter.getMaxRounds());
  ASSERT_TRUE(fresh_encounter.addEntity(boblin));
  ASSERT_EQ(4, fresh_encounter.getEntities().size());
  EXPECT_EQ(boblin, fresh_encounter.getEntities()[3]);
  EXPECT_EQ(0, fresh_encounter.getCurrentEntityIndex());
  EXPECT_EQ(1, fresh_encounter.getCurrentRound());
  EXPECT_EQ(5, fresh_encounter.getMaxRounds());
  ASSERT_TRUE(middle_encounter.addEntity(boblin));
  ASSERT_EQ(4, middle_encounter.getEntities().size());
  EXPECT_EQ(boblin, middle_encounter.getEntities()[3]);
  EXPECT_EQ(1, middle_encounter.getCurrentEntityIndex());
  EXPECT_EQ(3, middle_encounter.getCurrentRound());
  EXPECT_EQ(5, middle_encounter.getMaxRounds());
  ASSERT_TRUE(finished_encounter.addEntity(boblin));
  ASSERT_EQ(4, finished_encounter.getEntities().size());
  EXPECT_EQ(boblin, finished_encounter.getEntities()[3]);
  EXPECT_EQ(2, finished_encounter.getCurrentEntityIndex());
  EXPECT_EQ(5, finished_encounter.getCurrentRound());
  EXPECT_EQ(5, finished_encounter.getMaxRounds());

  boblin = Entity{"Boblin the fast", 20.20};
  ASSERT_TRUE(empty_encounter.addEntity(boblin));
  ASSERT_EQ(2, empty_encounter.getEntities().size());
  EXPECT_EQ(boblin, empty_encounter.getEntities()[0]);
  EXPECT_EQ(1, empty_encounter.getCurrentEntityIndex());
  EXPECT_EQ(1, empty_encounter.getCurrentRound());
  EXPECT_EQ(std::numeric_limits<std::size_t>::max(),
            empty_encounter.getMaxRounds());
  ASSERT_TRUE(fresh_encounter.addEntity(boblin));
  ASSERT_EQ(5, fresh_encounter.getEntities().size());
  EXPECT_EQ(boblin, fresh_encounter.getEntities()[0]);
  EXPECT_EQ(1, fresh_encounter.getCurrentEntityIndex());
  EXPECT_EQ(1, fresh_encounter.getCurrentRound());
  EXPECT_EQ(5, fresh_encounter.getMaxRounds());
  ASSERT_TRUE(middle_encounter.addEntity(boblin));
  ASSERT_EQ(5, middle_encounter.getEntities().size());
  EXPECT_EQ(boblin, middle_encounter.getEntities()[0]);
  EXPECT_EQ(2, middle_encounter.getCurrentEntityIndex());
  EXPECT_EQ(3, middle_encounter.getCurrentRound());
  EXPECT_EQ(5, middle_encounter.getMaxRounds());
  ASSERT_TRUE(finished_encounter.addEntity(boblin));
  ASSERT_EQ(5, finished_encounter.getEntities().size());
  EXPECT_EQ(boblin, finished_encounter.getEntities()[0]);
  EXPECT_EQ(3, finished_encounter.getCurrentEntityIndex());
  EXPECT_EQ(5, finished_encounter.getCurrentRound());
  EXPECT_EQ(5, finished_encounter.getMaxRounds());
}
} // namespace init_tracker
} // namespace nd
