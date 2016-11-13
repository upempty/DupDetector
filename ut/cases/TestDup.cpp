#include "Dup.h"

#include "gmock/gmock.h"

using ::testing::_;

TEST(TestDup, runDupSuccessfully)
{
  DupOptions options;
  options.dir = "../sample/test5";
  options.filter = (Filter)(COMMENT|BLANK|BRACE);
  options.jsonFile = "";
  options.minDupLines = DEFAULT_LINES;
  Dup dup(options);
  ASSERT_TRUE(dup.exec());
}
