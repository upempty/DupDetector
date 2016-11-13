#include "CmdParser.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

TEST(TestCmdParser, parsedAllParamsCorrectly)
{
  char * argv[] = {"clone_detect", "./src", "-cbn", "10", "-j", "clone_code.json"};
  int argc = sizeof(argv)/sizeof(char *);
  CmdParser cmdParser(argc, argv);
  DupOptions options;
  cmdParser.get(options);

  EXPECT_EQ("./src", options.dir); 
  EXPECT_EQ(COMMENT|BLANK|BRACE, options.filter); 
  EXPECT_EQ("clone_code.json", options.jsonFile); 
  EXPECT_EQ(10, options.minDupLines); 
}
