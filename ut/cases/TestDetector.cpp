#include "Detector.h"

#include "gmock/gmock.h"

using ::testing::_;

#define DEFAULT_LINES 5

class TestDetector : public ::testing::Test
{
public:
  Detector *detector;
  Codes codes;
  Text text1, text2;
  DupPairs dupPairs;

  virtual void SetUp()
  {
    detector = NULL;
  }
  virtual void TearDown()
  {

  }
  ~TestDetector()
  {
    if (detector != NULL)
      delete detector;
  }
};

TEST_F(TestDetector, findDuplicateIn2Files)
{
  text1.push_back(Line(1, "line1"));
  text1.push_back(Line(2, "line2"));
  text1.push_back(Line(3, "line3"));
  text1.push_back(Line(4, "line4"));
  text1.push_back(Line(5, "line5"));

  text2.push_back(Line(11, "line1"));
  text2.push_back(Line(12, "line2"));
  text2.push_back(Line(13, "line3"));
  text2.push_back(Line(14, "line4"));
  text2.push_back(Line(25, "line5"));
  codes.insert(std::make_pair("a.cpp", text1));
  codes.insert(std::make_pair("b.cpp", text2));
  detector = new Detector(codes, DEFAULT_LINES); 
  detector->findDup();
  dupPairs = detector->get();

  EXPECT_EQ(1, dupPairs.size());
}

TEST_F(TestDetector, findDuplicateInSameFile)
{
  text1.push_back(Line(1, "line1"));
  text1.push_back(Line(2, "line2"));
  text1.push_back(Line(3, "line3"));
  text1.push_back(Line(4, "line4"));
  text1.push_back(Line(5, "line5"));
  text1.push_back(Line(6, "line5"));

  text2.push_back(Line(11, "line1"));
  text2.push_back(Line(12, "line2"));
  text2.push_back(Line(13, "line3"));
  text2.push_back(Line(14, "line4"));
  text2.push_back(Line(25, "line5"));
  text2.push_back(Line(26, "line5"));
  codes.insert(std::make_pair("a.cpp", text1));
  codes.insert(std::make_pair("b.cpp", text2));
  detector = new Detector(codes, 6); 
  detector->findDup();
  dupPairs = detector->get();

  EXPECT_EQ(1, dupPairs.size());
}

TEST_F(TestDetector, noDupResultIfDupLineLessThan5In2File)
{
  text1.push_back(Line(1, "line1"));
  text1.push_back(Line(2, "line2"));
  text1.push_back(Line(3, "line3"));
  text1.push_back(Line(4, "line4"));
  text1.push_back(Line(5, "line5 the differ line"));

  text2.push_back(Line(11, "line1"));
  text2.push_back(Line(12, "line2"));
  text2.push_back(Line(13, "line3"));
  text2.push_back(Line(14, "line4"));
  text2.push_back(Line(25, "line5"));
  codes.insert(std::make_pair("a.cpp", text1));
  codes.insert(std::make_pair("b.cpp", text2));
  detector = new Detector(codes, DEFAULT_LINES); 
  detector->findDup();
  dupPairs = detector->get();

  EXPECT_EQ(0, dupPairs.size());
}

TEST_F(TestDetector, noDupResultIfDupLineLessThan5InSameFile)
{
  text1.push_back(Line(1, "line1"));
  text1.push_back(Line(2, "line2"));
  text1.push_back(Line(3, "line3"));
  text1.push_back(Line(4, "line4"));
  text1.push_back(Line(5, "line1"));

  text1.push_back(Line(6, "line2"));
  text1.push_back(Line(7, "line3"));
  text1.push_back(Line(8, "line4"));
  text1.push_back(Line(9, "line5"));
  text1.push_back(Line(25, "line5"));
  codes.insert(std::make_pair("a.cpp", text1));
  detector = new Detector(codes, DEFAULT_LINES); 
  detector->findDup();
  dupPairs = detector->get();

  EXPECT_EQ(0, dupPairs.size());
}
