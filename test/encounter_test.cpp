#include <algorithm>     // std::is_sorted()
#include <cstddef>       // std::size_t
#include <gtest/gtest.h> // testing::Test, TEST_F, EXPECT_*, ASSERT_*
#include <limits>        // std::numeric_limits
#include <utility>       // std::move()
#include <vector>        // std::vector, std::begin(), std::end()

#include "encounter.hpp"

namespace nd {
namespace init_tracker {
class EncounterTest : public testing::Test {
private:
  Encounter empty_encounter;
  Encounter fresh_encounter;
  Encounter middle_encounter;
  Encounter finished_encounter;

protected:
  std::vector<Entity> const encounter_entities = {Entity{"Barbarian", 10.08F},
                                                  Entity{"Rogue", 18.16F},
                                                  Entity{"Wizard", 13.10F}};

  EncounterTest() {
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

  Encounter& Empty() { return empty_encounter; }
  Encounter& Fresh() { return fresh_encounter; }
  Encounter& Middle() { return middle_encounter; }
  Encounter& Finished() { return finished_encounter; }
};

TEST_F(EncounterTest, NextTest) {
  EXPECT_EQ(Encounter::Finished, Empty().next());
  EXPECT_EQ(Encounter::NextEntity, Fresh().next());
  EXPECT_EQ(Encounter::NextEntity, Middle().next());
  EXPECT_EQ(Encounter::NextRound, Middle().next());
  EXPECT_EQ(Encounter::Finished, Finished().next());
}

TEST_F(EncounterTest, AddEntityTest) {
  Entity boblin{"Boblin", 7.09F};
  ASSERT_TRUE(Empty().addEntity(boblin));
  ASSERT_EQ(1, Empty().getEntities().size());
  EXPECT_EQ(boblin, Empty().getEntities()[0]);
  EXPECT_EQ(0, Empty().getCurrentEntityIndex());
  EXPECT_EQ(1, Empty().getCurrentRound());
  EXPECT_EQ(std::numeric_limits<std::size_t>::max(),
            Empty().getMaxRounds());
  ASSERT_TRUE(Fresh().addEntity(boblin));
  ASSERT_EQ(4, Fresh().getEntities().size());
  EXPECT_EQ(boblin, Fresh().getEntities()[3]);
  EXPECT_EQ(0, Fresh().getCurrentEntityIndex());
  EXPECT_EQ(1, Fresh().getCurrentRound());
  EXPECT_EQ(5, Fresh().getMaxRounds());
  ASSERT_TRUE(Middle().addEntity(boblin));
  ASSERT_EQ(4, Middle().getEntities().size());
  EXPECT_EQ(boblin, Middle().getEntities()[3]);
  EXPECT_EQ(1, Middle().getCurrentEntityIndex());
  EXPECT_EQ(3, Middle().getCurrentRound());
  EXPECT_EQ(5, Middle().getMaxRounds());
  ASSERT_TRUE(Finished().addEntity(boblin));
  ASSERT_EQ(4, Finished().getEntities().size());
  EXPECT_EQ(boblin, Finished().getEntities()[3]);
  EXPECT_EQ(2, Finished().getCurrentEntityIndex());
  EXPECT_EQ(5, Finished().getCurrentRound());
  EXPECT_EQ(5, Finished().getMaxRounds());

  boblin = Entity{"Boblin the fast", 20.20F};
  ASSERT_TRUE(Empty().addEntity(boblin));
  ASSERT_EQ(2, Empty().getEntities().size());
  EXPECT_EQ(boblin, Empty().getEntities()[0]);
  EXPECT_EQ(1, Empty().getCurrentEntityIndex());
  EXPECT_EQ(1, Empty().getCurrentRound());
  EXPECT_EQ(std::numeric_limits<std::size_t>::max(),
            Empty().getMaxRounds());
  ASSERT_TRUE(Fresh().addEntity(boblin));
  ASSERT_EQ(5, Fresh().getEntities().size());
  EXPECT_EQ(boblin, Fresh().getEntities()[0]);
  EXPECT_EQ(1, Fresh().getCurrentEntityIndex());
  EXPECT_EQ(1, Fresh().getCurrentRound());
  EXPECT_EQ(5, Fresh().getMaxRounds());
  ASSERT_TRUE(Middle().addEntity(boblin));
  ASSERT_EQ(5, Middle().getEntities().size());
  EXPECT_EQ(boblin, Middle().getEntities()[0]);
  EXPECT_EQ(2, Middle().getCurrentEntityIndex());
  EXPECT_EQ(3, Middle().getCurrentRound());
  EXPECT_EQ(5, Middle().getMaxRounds());
  ASSERT_TRUE(Finished().addEntity(boblin));
  ASSERT_EQ(5, Finished().getEntities().size());
  EXPECT_EQ(boblin, Finished().getEntities()[0]);
  EXPECT_EQ(3, Finished().getCurrentEntityIndex());
  EXPECT_EQ(5, Finished().getCurrentRound());
  EXPECT_EQ(5, Finished().getMaxRounds());
}

TEST_F(EncounterTest, RemoveEntityTest) {
  ASSERT_FALSE(Empty().removeEntity(1));
  ASSERT_TRUE(Fresh().removeEntity(1));
  ASSERT_EQ(2, Fresh().getEntities().size());
  EXPECT_EQ(0, Fresh().getCurrentEntityIndex());
  EXPECT_EQ(1, Fresh().getCurrentRound());
  EXPECT_EQ(5, Fresh().getMaxRounds());
  ASSERT_TRUE(Middle().removeEntity(1));
  ASSERT_EQ(2, Middle().getEntities().size());
  EXPECT_EQ(1, Middle().getCurrentEntityIndex());
  EXPECT_EQ(3, Middle().getCurrentRound());
  EXPECT_EQ(5, Middle().getMaxRounds());
  ASSERT_TRUE(Finished().removeEntity(1));
  ASSERT_EQ(2, Finished().getEntities().size());
  EXPECT_EQ(1, Finished().getCurrentEntityIndex());
  EXPECT_EQ(5, Finished().getCurrentRound());
  EXPECT_EQ(5, Finished().getMaxRounds());
  ASSERT_TRUE(AreEntitiesSorted());
}
} // namespace init_tracker
} // namespace nd
