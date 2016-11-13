#ifndef _DETECTOR_H_
#define _DETECTOR_H_

#include <unordered_map>
#include <iostream>
#include "Reader.h"

class DupPair;
class DupRec;

typedef std::vector<std::pair<std::string, unsigned int> > FileLines;
typedef std::unordered_map<std::string, FileLines> LineBuckets;
typedef std::list<DupPair> DupPairs;

class Detector
{
public:
  Detector() {};
  ~Detector() {};
  Detector(Codes &codes, int minDupLines);
  void createDupBuckets(void);
  void findDup(void);
  DupPairs get(void)
  {
    return _dupPairs;
  }

private:
  void initLineTable(void);
  void filterDupLines(void);
  void calcDuplicate(std::string srcFile, Line &lineSrc, 
                     std::string desFile, Line &lineDes);
  void generateDupPair(DupRec src, DupRec des);
  void removeSubPairs(void);

private:
  LineBuckets _buckets; 
  DupPairs _dupPairs;
  unsigned int _minDupLines;
  Codes _codes;
};

class DupRec
{
public:
  DupRec() {};
  DupRec(std::string file, unsigned int start, unsigned int end)
  {
    this->file = file;
    this->startLine = start;
    this->endLine = end;
  }
  DupRec &operator = (const DupRec &s)
  {
    this->file = s.file;
    this->startLine = s.startLine;
    this->endLine = s.endLine;
    return *this;
  }
  bool contain(DupRec &dup)
  {
    if (this->file.compare(dup.file) != 0)
    {
      return false;
    }
    return ((this->startLine <= dup.startLine) && 
            (this->endLine >= dup.endLine));
  }

  std::string file;
  unsigned int startLine;
  unsigned int endLine;
}; 

class DupPair 
{
public:
  DupPair() {};
  ~DupPair() {};
  DupPair(DupRec &s, DupRec &d)
  {
    src = s;
    des = d;
  }

  bool contain(DupPair &dupPair)
  {
    return (this->src.contain(dupPair.src) && 
            this->des.contain(dupPair.des));
  }

  DupRec src;
  DupRec des;
};

#endif
