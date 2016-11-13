#include "Serializer.h"

#include "gmock/gmock.h"

using ::testing::_;

class TestSerializer : public ::testing::Test
{
public:
  Serializer *serializer;
  DupPairs dupPairs;
  std::string outFile;
  std::string output;

  virtual void SetUp()
  {
    serializer = NULL;
  }
  virtual void TearDown()
  {

  }
  ~TestSerializer()
  {
    if (serializer != NULL)
      delete serializer;
  }
};

  std::string expectOutput = "{\n\
\"totalDuplicate\": 15,\n\
\"results\": [\n\
{\n\
\"duplicate\": 15,\n\
\"fileName1\": \"a.cpp\",\n\
\"fileName2\": \"5.cpp\",\n\
\"details\": [\n\
{\n\
\"duplicate\": 15,\n\
\"startLine1\": 1,\n\
\"lineNumber1\": 5,\n\
\"startLine2\": 1,\n\
\"lineNumber2\": 10\n\
}\n\
]\n\
}\n\
]\n\
}\n";
 
TEST_F(TestSerializer, writeEmptyToConsole)
{
  serializer = new Serializer(dupPairs, outFile);
  output = serializer->write();

  EXPECT_EQ(0, output.length());
}
 
TEST_F(TestSerializer, write3DupBlocksToConsole)
{
  DupRec src1("a.cpp", 1, 5);
  DupRec des1("5.cpp", 1, 10);
  DupRec src11("a.cpp", 100, 104);
  DupRec des11("5.cpp", 100, 104);
  dupPairs.push_back(DupPair(src1, des1));
  dupPairs.push_back(DupPair(src11, des11));
  DupRec src2("a.cpp", 11, 20);
  DupRec des2("55.cpp", 1, 10);
  dupPairs.push_back(DupPair(src2, des2));
  serializer = new Serializer(dupPairs, outFile);
  output = serializer->write();

  EXPECT_EQ("totalDuplicate: 45\n", output);
}
 
TEST_F(TestSerializer, writeEmptyToJson)
{
  outFile = "json.json";
  serializer = new Serializer(dupPairs, outFile);
  output = serializer->write();

  EXPECT_EQ(0, output.length());
}
 
TEST_F(TestSerializer, writeToJsonFile)
{
  outFile = "a.txt";
  DupRec src("a.cpp", 1, 5);
  DupRec des("5.cpp", 1, 10);
  dupPairs.push_back(DupPair(src, des));
  serializer  = new Serializer(dupPairs, outFile);
  output = serializer->write();

  EXPECT_EQ(expectOutput, output);
} 

TEST_F(TestSerializer, write3DupBlocksToJsonFile)
{
  outFile = "3json.json";
  DupRec src1("a.cpp", 1, 5);
  DupRec des1("5.cpp", 1, 10);
  DupRec src11("a.cpp", 100, 104);
  DupRec des11("5.cpp", 100, 104);
  dupPairs.push_back(DupPair(src1, des1));
  dupPairs.push_back(DupPair(src11, des11));
  DupRec src2("a.cpp", 11, 20);
  DupRec des2("55.cpp", 1, 10);
  dupPairs.push_back(DupPair(src2, des2));
  serializer = new Serializer(dupPairs, outFile);
  output = serializer->write();
  size_t pos = output.find("\"totalDuplicate\": 45");

  ASSERT_TRUE(pos != std::string::npos);
}
