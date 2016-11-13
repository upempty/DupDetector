#include <iostream>
#include <stdexcept>

#include "Serializer.h"

static std::map<int, Output*> _formats;
 
void Serializer::initFormats(DupPairs &dupPairs)
{
  _formats[CONSOLE] = new Console(dupPairs);
  _formats[JSON] = new Json(dupPairs);
}

Serializer::Serializer(DupPairs &dupPairs, std::string jsonFile)
{
  initFormats(dupPairs);
  _file = jsonFile;
  _formatType = _file.empty() ? CONSOLE : JSON;
  _outFormat = _formats.at(_formatType);
}

std::string & Serializer::write(void) 
{
  _outFormat->dump(_output);
  if (_output.empty())
  {
#ifndef __UT__
    std::cout<<"No Duplicaton"<<std::endl;
#endif
    return _output;
  }
  if (_formatType == CONSOLE)
  {
#ifndef __UT__
    std::cout<<_output; 
#endif
  }
  else
  {
    _of.open(_file);
    if (!_of.is_open())
    {
      throw std::runtime_error("Open json file failure");
    }
    _of<<_output;
    _of.close();
  }
  return _output;
} 
