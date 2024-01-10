#include <gtest/gtest.h> // testing::Test, ASSERT_*, EXPECT_*
#include <sstream>       // std::ostringstream

#include "entity.hpp"

namespace nd {
namespace init_tracker {
class EntityTest : public testing::Test {
protected:
  Entity const e0 = Entity{"entity", 1.2F};
  Entity const e1 = Entity{"entity", 1.2F, 1};
  Entity const e2 = Entity{"other entity", 3.2F, 4};

  void SetUp() override {
    ASSERT_EQ(e0.getName(), "entity");
    ASSERT_EQ(e0.getInitiative(), 1.2F);
    ASSERT_EQ(e0.getFirstRound(), 1);
    ASSERT_EQ(e1.getName(), "entity");
    ASSERT_EQ(e1.getInitiative(), 1.2F);
    ASSERT_EQ(e1.getFirstRound(), 1);
    ASSERT_EQ(e2.getName(), "other entity");
    ASSERT_EQ(e2.getInitiative(), 3.2F);
    ASSERT_EQ(e2.getFirstRound(), 4);
  }
};

TEST_F(EntityTest, EqualityTest) {
  EXPECT_TRUE(e0.Equals(e1));
  EXPECT_TRUE(e1.Equals(e0));
  EXPECT_EQ(e0, e1);
  EXPECT_EQ(e1, e0);
  EXPECT_FALSE(e0.Equals(e2));
  EXPECT_FALSE(e2.Equals(e0));
  EXPECT_NE(e0, e2);
  EXPECT_NE(e2, e0);
}

TEST_F(EntityTest, OStreamTest) {
  using namespace std::string_literals;

  std::ostringstream teststream;
  teststream << e0;
  EXPECT_EQ(teststream.str(), "entity (1.20)"s);
  teststream = std::ostringstream{};
  teststream << e1;
  EXPECT_EQ(teststream.str(), "entity (1.20)"s);
  teststream = std::ostringstream{};
  teststream << e2;
  EXPECT_EQ(teststream.str(), "other entity (3.20)"s);
}
} // namespace init_tracker
} // namespace nd
