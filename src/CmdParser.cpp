#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "CmdParser.h"

#define EOF (-1)

CmdParser::CmdParser(int argc, char *argv[])
{
  _program = argv[0];
  _options.dir.clear();
  _options.filter = BLANK;
  _options.jsonFile.clear();
  _options.minDupLines = DEFAULT_LINES;
  parseOptions(argc, argv);
}

void CmdParser::getOpt(DupOptions &options, int argc, char *argv[])
{
  int opt, lines = 0;
  while((opt = getopt(argc, argv, "hbcj:n:")) != EOF)
  {
    switch(opt)
    {
    case 'b':
      options.filter =(Filter)(_options.filter|BRACE);
      break;
    case 'c':
      options.filter =(Filter)(_options.filter|COMMENT);
      break;
    case 'j':
      options.jsonFile = optarg;
      break;
    case 'n':
      if ((lines=atoi(optarg)) <= 0)
      {
        helpPrompt();
        throw std::runtime_error("Illegal param: "+std::string(optarg));
      }
      options.minDupLines = lines;
      break;
    default:
      helpPrompt();
      throw std::runtime_error("Error params!");
    }
  }
}

void CmdParser::parseOptions(int argc, char *argv[])
{
  if (argc < 2)
  {
    helpPrompt();
    throw std::runtime_error("The directory should be specified!");
  }
  _options.dir = argv[1];
  if(_options.dir.find('-') == 0)
  {
    helpPrompt();
    throw std::runtime_error("First param should be the directory!");
  }
  getOpt(_options, argc, argv);  
}

void CmdParser::get(DupOptions &options)
{
  options = _options;
}

void CmdParser::helpPrompt(void)
{
  std::cout<<"Usage: "<<_program<<" <directory> [options]\n"
           <<"Options:\n"
           <<"\t-h,--Show the help message\n"
           <<"\t-c,--Ignore comments\n"
           <<"\t-b,--Brace '{' or '}' should be considered as a new line\n"
           <<"\t-n,--Duplicate line at least, default is 5\n"
           <<"\t-j,--Specify the Json file\n\n"
           <<"\tExample:./clone_deetect src -cbn 10 -j clone.json\n"
           <<std::endl;
}
