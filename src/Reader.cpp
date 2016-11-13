#include <iostream>
#include "Reader.h"

Line::Line(unsigned int id, std::string str)
{
  this->id = id;
  this->str = str;
}

bool Line::operator==(const Line &line)
{
  return ((this->id == line.id) && 
          (this->str.compare(line.str) == 0));
}

bool Line::operator>=(const Line &line)
{
  return (this->id >= line.id); 
}

Reader::Reader(Files &files)
{
  _files = files;
}

void Reader::scan(Codes &codes)
{
  codes.clear();
  for(std::string file : _files)
  {
    Text text = load(file);
    if (text.size() == 0)
    {
      continue;
    }
    codes[file] = text;
  }
}

Text &Reader::load(const std::string &file)
{
  Line line;

  _text.clear();
  _inFile.open(file.c_str());  
  if (!_inFile.is_open())
  {
    //std::cout<<"Open file:"<<file<<" failed"<<std::endl;
    return _text;
  }

  unsigned int lineIndex = 0;
  while(!_inFile.eof())
  {
    std::getline(_inFile, line.str);
    line.id = ++lineIndex;
    _text.push_back(line);
  }
  _inFile.close();
  return _text;
}
