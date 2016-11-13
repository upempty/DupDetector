#ifndef _READER_H_
#define _READER_H_

#include <list>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "Dir.h"

class Line
{
public:
  Line(unsigned int id, std::string str);
  Line(){};
  ~Line(){};
  unsigned int id;
  std::string str;
  bool operator==(const Line &line);   
  bool operator>=(const Line &line);   
};

typedef std::list<Line> Text;
typedef std::map<std::string, Text> Codes; 

class Reader
{
public:
  Reader(Files &files);
  ~Reader() {};
  void scan(Codes &codes);

private:
  Text &load(const std::string &file);
  Files _files;
  Codes _codes;

  std::ifstream _inFile;
  Text _text;
};

#endif
