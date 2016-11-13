#include <iostream>
#include <algorithm>

#include "Detector.h"

Detector::Detector(Codes &codes, int minDupLines)
{
  _codes = codes;
  _minDupLines = minDupLines;
  createDupBuckets();
}

void Detector::createDupBuckets(void)
{
  initLineTable();
  filterDupLines();
}

void Detector::initLineTable(void)
{
  _buckets.clear();
  for(Codes::iterator it = _codes.begin(); it != _codes.end(); it++)
  {
    std::string fileName = it->first;
    Text t = it->second;
    for(Text::iterator it2 = t.begin(); it2 != t.end(); it2++)
    {
      if (_buckets.find(it2->str) == _buckets.end())
      {
        FileLines fileLines;
        fileLines.clear();
        fileLines.push_back(std::make_pair(fileName, it2->id));
        _buckets[it2->str] = fileLines; 
      }
      else
      {
        _buckets[it2->str].push_back(std::make_pair(fileName, it2->id));
      }
    }
  }
}

void Detector::filterDupLines(void)
{
  LineBuckets::iterator it = _buckets.begin();
  while(it != _buckets.end())
  {
    if (it->second.size() == 1)
    {
      _buckets.erase(it++);
      continue;
    }
    it++;
  } 
}

void Detector::findDup(void)
{
  for(LineBuckets::iterator it = _buckets.begin(); it != _buckets.end(); it++)
  {
    FileLines fileLines = it->second;
    for(FileLines::iterator it1 = fileLines.begin(); it1 != fileLines.end(); it1++)
    {
      for(FileLines::iterator it2 = (it1 + 1); it2 != fileLines.end(); it2++)
      {
        Line srcLine(it1->second, it->first);
        Line desLine(it2->second, it->first);
        std::string srcFile = it1->first;
        std::string desFile = it2->first;
        calcDuplicate(srcFile, srcLine, desFile, desLine);
      }
    }
  } 
  removeSubPairs();
}

void Detector::calcDuplicate(std::string srcFile, Line &srcLine, 
                             std::string desFile, Line &desLine)
{
  Text textSrc = _codes.find(srcFile)->second;
  Text textDes = _codes.find(desFile)->second;
  Text::iterator itLineSrc = std::find(textSrc.begin(), textSrc.end(), srcLine);
  Text::iterator itLineDes = std::find(textDes.begin(), textDes.end(), desLine);
  unsigned int dupLineNum = 0;
  do
  {
    dupLineNum++; 
    itLineSrc++; itLineDes++;
    if ((itLineSrc == textSrc.end()) || (itLineDes == textDes.end()))
      break;
    if ((srcFile.compare(desFile) == 0) && ((*itLineSrc) >= desLine))
      break; 
    if ((_buckets.find(itLineSrc->str) == _buckets.end()) || 
        (_buckets.find(itLineDes->str) == _buckets.end()))
      break;
  }
  while((itLineSrc->str).compare(itLineDes->str) == 0);
  if (dupLineNum >= _minDupLines)
  {
    Text::iterator itLine1 = --itLineSrc;
    Text::iterator itLine2 = --itLineDes;
    DupRec src(srcFile, srcLine.id, itLine1->id);
    DupRec des(desFile, desLine.id, itLine2->id);
    generateDupPair(src, des); 
  }
}

void Detector::generateDupPair(DupRec src, DupRec des) 
{
  if (((src.endLine + 1 - src.startLine) < _minDupLines) ||
      ((des.endLine + 1 - des.startLine) < _minDupLines))
    return;
  DupPair pair(src, des);
  _dupPairs.push_back(pair); 
}

void Detector::removeSubPairs(void)
{
  for(DupPairs::iterator it1 = _dupPairs.begin(); it1 != _dupPairs.end(); it1++)
  {
    DupPairs::iterator it2 = _dupPairs.begin();
    while(it2 != _dupPairs.end())
    {
      if (it1 == it2)
      {
        it2++;
        continue;
      }
      if (it1->contain(*it2))
      {
        it2 = _dupPairs.erase(it2);
      }
      else
      {
        it2++;
      }
    }
  }
}
