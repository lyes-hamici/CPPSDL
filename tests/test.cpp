#include <iostream>
#include <gtest/gtest.h>
#include "../src/Game/File.hpp"

TEST(FileTest, LoadSave)
{
    EXPECT_EQ(File::saveScore(667,"Score.save"), 0);
    EXPECT_EQ(File::loadScore("Score.save"), 667);

    EXPECT_EQ(File::saveScore(111111, "Score.save"), 0);
    EXPECT_EQ(File::loadScore("Score.save"), 111111);
}

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}