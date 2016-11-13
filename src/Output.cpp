#include <algorithm>

#include "Detector.h"
#include "Output.h"

Console::Console(DupPairs &dupPairs) : Output(dupPairs)
{
  _dupPairs = dupPairs;
  calcTotalDup();
}

void Console::calcTotalDup(void)
{
  _totalDup = 0;
  for(DupPairs::iterator it = _dupPairs.begin(); it != _dupPairs.end(); it++)
  {
    _totalDup += it->src.endLine + 1 - it->src.startLine + it->des.endLine + 1 - it->des.startLine;
  }
}

void Console::dump(std::string &output)
{
  if (_dupPairs.size() == 0)
  {
    return;
  }
  _ss<<"totalDuplicate: "<<_totalDup<<"\n";
  output = _ss.str();
}


Json::Json(DupPairs &dupPairs) : Output(dupPairs)
{
  _dupPairs = dupPairs;
  classify();
  sort();
}

void Json::classify(void)
{
  _totalDup = 0;
  for(DupPairs::iterator it = _dupPairs.begin(); it != _dupPairs.end(); it++)
  {
    std::string key = it->src.file+it->des.file;
    DupElem dupElem;
    dupElem.start1 = it->src.startLine;
    dupElem.lines1 = it->src.endLine + 1 - it->src.startLine;
    dupElem.start2 = it->des.startLine;
    dupElem.lines2 = it->des.endLine + 1 - it->des.startLine;
    dupElem.totalDup = dupElem.lines1 + dupElem.lines2;
    if (_files.find(key) == _files.end())
    {
      FilePair file;
      file.totalDup = dupElem.totalDup;
      file.src = it->src.file;
      file.des = it->des.file;
      file.dupDetail.push_back(dupElem);
      _files[key] = file;
    }
    else
    {
      _files[key].dupDetail.push_back(dupElem);
      _files[key].totalDup += dupElem.totalDup;
    }
    _totalDup += dupElem.totalDup;
  }
}

void Json::sort(void)
{

  FilePairs::iterator it = _files.begin();
  while(it != _files.end())
  {
    it->second.dupDetail.sort();
    it++;
  }
}


void Json::dump(std::string &output)
{
  if (_files.size() == 0)
  {
    return;
  }
  _ss<<"{"<<"\n";
  _ss<<"\""<<"totalDuplicate"<<"\": "<<_totalDup<<",\n";
  _ss<<"\""<<"results"<<"\": [\n";

  FilePairs::iterator it= _files.begin();
  _ss<<it->second.toStream();
  while(++it != _files.end())
  {
    _ss<<","<<"\n";
    _ss<<it->second.toStream();
  }

  _ss<<"\n]\n";
  _ss<<"}\n";

  output = _ss.str();
}

DupElem::DupElem(const DupElem &elem)
{
  (*this) = elem;
}

DupElem &DupElem::operator = (const DupElem &elem)
{
  totalDup = elem.totalDup;
  start1 = elem.start1;
  lines1 = elem.lines1;
  start2 = elem.start2;
  lines2 = elem.lines2;
  return *this;
}

bool DupElem::operator < (const DupElem &elem)
{
  return start1 < elem.start1;
}

std::string DupElem::toStream(void)
{
  _ss<<"{\n";

  _ss<<"\""<<"duplicate"<<"\": "<<totalDup<<",\n";
  _ss<<"\""<<"startLine1"<<"\": "<<start1<<",\n";
  _ss<<"\""<<"lineNumber1"<<"\": "<<lines1<<",\n";
  _ss<<"\""<<"startLine2"<<"\": "<<start2<<",\n";
  _ss<<"\""<<"lineNumber2"<<"\": "<<lines2<<"\n";

  _ss<<"}";
  return _ss.str();
}

FilePair::FilePair(const FilePair &file)
{
  (*this) = file;
}

FilePair &FilePair::operator = (const FilePair &file)
{
  src = file.src;
  des = file.des;
  totalDup = file.totalDup;
  dupDetail = file.dupDetail;
  return *this;
}

std::string FilePair::toStream(void)
{
  _ss<<"{\n";
  _ss<<"\""<<"duplicate"<<"\": "<<totalDup<<",\n";
  _ss<<"\""<<"fileName1"<<"\": \""<<src<<"\",\n";
  _ss<<"\""<<"fileName2"<<"\": \""<<des<<"\",\n";
  _ss<<"\""<<"details"<<"\": [\n";
  std::list<DupElem>::iterator it= dupDetail.begin();
  _ss<<it->toStream();
  while(++it != dupDetail.end())
  {
    _ss<<","<<"\n";
    _ss<<it->toStream();
  }
  _ss<<"\n";
  _ss<<"]\n";
  _ss<<"}";
  return _ss.str();
}
