#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <map>
#include <fstream>
#include <sstream>
#include "Detector.h"

class DupElem;
class FilePair;

class Output
{
public:
  Output(DupPairs &dupPairs) : _dupPairs(dupPairs) {};
  virtual ~Output() {};
  virtual void dump(std::string &str) = 0;
private:
  DupPairs _dupPairs;
};

class Console : public Output
{
public:
  virtual ~Console() {};
  Console(DupPairs &dupPairs);
  virtual void dump(std::string &output);

private:
  void calcTotalDup(void);

private: 
  DupPairs _dupPairs;
  std::stringstream _ss;
  int _totalDup;
};

typedef std::map<std::string, FilePair> FilePairs;

class Json : public Output
{
public:
  virtual ~Json() {};
  Json(DupPairs &dupPairs);
  virtual void dump(std::string &output);

private: 
  void classify(void);
  void sort(void);

private:
  DupPairs _dupPairs;
  std::stringstream _ss;
  int _totalDup;
  FilePairs _files;
}; 

class DupElem
{
public:
  DupElem() {}
  DupElem(int, int, int, int, int);
  ~DupElem() {}
  DupElem(const DupElem &elem);
  DupElem &operator = (const DupElem &elem);
  bool operator < (const DupElem &elem);
  std::string toStream(void);

  int totalDup;
  int start1;
  int lines1;
  int start2;
  int lines2;

private:
  std::stringstream _ss;
};

class FilePair
{
public:
  FilePair() {};
  ~FilePair() {};
  FilePair(const FilePair &file);
  FilePair &operator = (const FilePair &file);
  std::string toStream(void);

  int totalDup;
  std::string src;
  std::string des;
  std::list<DupElem> dupDetail;

private:
  std::stringstream _ss;
};

#endif
