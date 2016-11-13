#include "Dir.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::ElementsAre;

class TestDir : public ::testing::Test
{
public:
  Dir dir;
  Files files;
  virtual void SetUp()
  {
    files.clear();
  };
  virtual void TearDown()
  {
  };
  virtual ~TestDir(){};
};

TEST_F(TestDir, listAll5typesSourceCodeFiles)
{
  files = dir.searchFiles("../sample/test1/");
  ASSERT_THAT(files, 
              ElementsAre("../sample/test1/src/a.c", 
                          "../sample/test1/src/b.cc",
                          "../sample/test1/src/c.cpp",
                          "../sample/test1/src/d.h",
                          "../sample/test1/src/e.hpp"));
}

TEST_F(TestDir, listEmptyWhenDirNotExist)
{
  files = dir.searchFiles("../sample/testnone");
  ASSERT_TRUE(files.empty());
}

TEST_F(TestDir, listEmptyWhenNoneSourceCodeIncluded)
{
  files = dir.searchFiles("../sample/no_match"); 
  EXPECT_EQ(0, files.size()); 
}
