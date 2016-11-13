#include "Reader.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

class TestReader : public ::testing::Test
{
public:
  Codes expectCodes, codes;
  Text expectTextx, expectTexty, expectTextz;
  Files files;
  virtual void SetUp()
  {
  }
  virtual void TearDown()
  {
  }
  virtual ~TestReader() {}
  void codesCompare(Codes &expectCodes, Codes &codes)
  {
    for(Codes::iterator itCodes1 = expectCodes.begin(), itCodes2 = codes.begin();
        itCodes1 != expectCodes.end() && itCodes2 != codes.end();
        itCodes1++, itCodes2++)
    {
      Text expectText = itCodes1->second;
      Text text = itCodes2->second;
      EXPECT_EQ(itCodes1->first, itCodes2->first);
      for(Text::iterator it1 = expectText.begin(), it2 = text.begin(); 
          it1 != expectText.end() || it2 != text.end();  
          it1++, it2++)
      {
        ASSERT_TRUE(*it1 == *it2);
      }
    }
  }
};

TEST_F(TestReader, getCodesFrom2Files)
{
  std::string file1 = "../sample/test2/y.cpp";
  std::string file2 = "../sample/test2/z.cpp";
  expectTexty.push_back(Line(1, "#include \"y.h\""));
  expectTexty.push_back(Line(2, "int main()"));
  expectTexty.push_back(Line(3, "{"));
  expectTexty.push_back(Line(4, "  return 0;"));
  expectTexty.push_back(Line(5, "}"));
  expectTexty.push_back(Line(6, ""));
  expectTextz.push_back(Line(1, "#include \"y.h\""));
  expectTextz.push_back(Line(2, ""));
  expectCodes[file1] = expectTexty; 
  expectCodes[file2] = expectTextz; 
  files.push_back(file1);
  files.push_back(file2);
  Reader reader(files);
  reader.scan(codes);

  codesCompare(expectCodes, codes);
}

TEST_F(TestReader, getCodesFromEmptyFile)
{
  std::string file1 = "../sample/test2/x.cpp";
  expectTextx.push_back(Line(1, ""));
  expectCodes[file1] = expectTextx; 
  files.push_back(file1);
  Reader reader(files);
  reader.scan(codes);

  codesCompare(expectCodes, codes);
}

TEST_F(TestReader, getCodesFromNoneExistFile)
{
  std::string file1 = "../sample/test2/openFileFailed.cpp";
  expectTextx.push_back(Line(1, "Fake"));
  expectCodes[file1] = expectTextx; 
  files.push_back(file1);
  Reader reader(files);
  reader.scan(codes);

  EXPECT_EQ(0, codes.size());
}
