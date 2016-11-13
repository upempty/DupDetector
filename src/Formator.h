#ifndef _FORMATOR_H_
#define _FORMATOR_H_

#include "CmdParser.h"
#include "Reader.h"
#include "Rule.h"

typedef std::vector<Rule *> Rules;

class Formator
{
public:
  Formator(std::string dir, Filter ruleFlag);
  ~Formator() {};
  void format(Codes &codes);
  void parse(Text &text);

  void refresh(Codes &codes);

private:
  Rules createRules(Filter input);

  Rules _priorRules;

  Dir *_dir;
  Files _files; 
  Reader *_reader;
};

#endif
