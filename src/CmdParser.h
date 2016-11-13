#ifndef _CMDPARSER_H_
#define _CMDPARSER_H_

#include <string>

#define DEFAULT_LINES 5

enum Filter
{
  COMMENT = 1 << 0,
  BLANK   = 1 << 1,
  BRACE   = 1 << 2,
};

struct DupOptions
{
  std::string dir;
  Filter filter; 
  std::string jsonFile;
  unsigned int minDupLines;
};

class CmdParser
{
public:
  CmdParser() {}
  CmdParser(int argc, char *argv[]);
  ~CmdParser() {}
  void parseOptions(int argc, char *argv[]);
  void get(DupOptions &options);

private:
  void getOpt(DupOptions &options, int argc,char *argv[]);
  void helpPrompt(void);
  DupOptions _options;
  std::string _program;
};

#endif
