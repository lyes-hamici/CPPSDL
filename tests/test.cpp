#include <iostream>
#include <gtest/gtest.h>
#include "../src/Game/File.hpp"

TEST(FileTest, LoadSaveScore)
{
    File::saveScore(667, "Score.save");
    EXPECT_EQ(File::loadScore("Score.save"), 667);

    File::saveScore(111111, "Score.save");
    EXPECT_EQ(File::loadScore("Score.save"), 111111);
}

TEST(FileTest, SaveInvalidScore)
{
    int invalidScore = -1;
    File::saveScore(invalidScore, "Score.save");
    EXPECT_EQ(File::loadScore("Score.save"), 111111); 
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
