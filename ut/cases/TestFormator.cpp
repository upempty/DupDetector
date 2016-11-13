#include "Formator.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

class TestFormator : public ::testing::Test
{
public:
  Formator *formator;
  Codes expectCodes, codes;
  Text expectTexty, expectTextz;

  virtual void SetUp()
  {
    formator = NULL;
  }
  virtual void TearDown()
  {

  }
  ~TestFormator() 
  {
    if (formator != NULL) 
      delete formator;
  }
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

TEST_F(TestFormator, removeBlanksDefaultly)
{
  formator = new Formator("../sample/test2", (Filter)0);
  formator->refresh(codes);
  std::string file1 = "../sample/test2/y.cpp";
  std::string file2 = "../sample/test2/z.cpp";
  expectTexty.push_back(Line(1, "#include\"y.h\""));
  expectTexty.push_back(Line(2, "intmain()"));
  expectTexty.push_back(Line(3, "{"));
  expectTexty.push_back(Line(4, "return0;"));
  expectTexty.push_back(Line(5, "}"));
  expectTextz.push_back(Line(1, "#include\"y.h\""));
  expectCodes[file1] = expectTexty; 
  expectCodes[file2] = expectTextz; 

  codesCompare(expectCodes, codes);
}

TEST_F(TestFormator, ignoreComments)
{
  formator = new Formator("../sample/test3", (Filter)(COMMENT+BLANK));
  formator->refresh(codes);
  std::string file1 = "../sample/test3/comments.hpp";
  expectTexty.push_back(Line(1, "#defineCOUNT100"));
  expectTexty.push_back(Line(2, "inta=5;"));
  expectTexty.push_back(Line(6, "a=a*COUNT;"));
  expectCodes[file1] = expectTexty; 

  codesCompare(expectCodes, codes);
}

TEST_F(TestFormator, changeToNewLineWhenMeetsBrace)
{
  formator = new Formator("../sample/test4", (Filter)(BRACE+BLANK));
  formator->refresh(codes);
  std::string file1 = "../sample/test4/brace.cc";
  expectTexty.push_back(Line(1, "#include<iostream>"));
  expectTexty.push_back(Line(2, "intmain()"));
  expectTexty.push_back(Line(2, "{"));
  expectTexty.push_back(Line(3, "boola=true;"));
  expectTexty.push_back(Line(4, "if(a)"));
  expectTexty.push_back(Line(4, "{"));
  expectTexty.push_back(Line(5, "std::cout<<\"true\"<<std::endl;"));
  expectTexty.push_back(Line(5, "}"));
  expectTexty.push_back(Line(6, "}"));
  expectCodes[file1] = expectTexty; 

  codesCompare(expectCodes, codes);
}

TEST_F(TestFormator, processCommentBlankAndBraceProperly)
{
  formator = new Formator("../sample/test42", (Filter)(COMMENT+BRACE+BLANK));
  formator->refresh(codes);
  std::string file1 = "../sample/test42/brace_comment.cc";
  expectTexty.push_back(Line(1, "#include<iostream>"));
  expectTexty.push_back(Line(3, "intmain()"));
  expectTexty.push_back(Line(3, "{"));
  expectTexty.push_back(Line(4, "boola=true;"));
  expectTexty.push_back(Line(5, "if(a)"));
  expectTexty.push_back(Line(5, "{"));
  expectTexty.push_back(Line(6, "std::cout<<\"true\"<<std::endl;"));
  expectTexty.push_back(Line(6, "}"));
  expectTexty.push_back(Line(6, "return0;"));
  expectTexty.push_back(Line(7, "}"));
  expectCodes[file1] = expectTexty; 

  codesCompare(expectCodes, codes);
}
