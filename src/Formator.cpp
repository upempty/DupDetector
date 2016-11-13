#include "Formator.h"

struct RuleTable
{
  Filter Type;
  Rule *rule;
};

// Priority rules from high to low
static const RuleTable ruleTable[] = {
  {COMMENT, new CommentRule()},
  {BLANK, new BlankRule()},
  {BRACE, new BraceRule()},
};

Rules Formator::createRules(Filter input)
{
  Rules group;
  for(size_t i = 0; i < sizeof(ruleTable)/sizeof(RuleTable); i++)
  {
    if (ruleTable[i].Type && input)
    {
      group.push_back(ruleTable[i].rule);
    }
  }
  if (group.size() == 0)
  {
    //default using BLANK filter
    group.push_back(ruleTable[BLANK>>1].rule);
  }
  return group;
}

Formator::Formator(std::string dir, Filter ruleFlag)
{
  _dir = new Dir();  
  _files = _dir->searchFiles(dir);
  _priorRules = createRules(ruleFlag);
}

void Formator::parse(Text &text)
{
  for(Rule *rule : _priorRules)
  {
    rule->handle(text);
  }
}

void Formator::format(Codes &codes)
{
  Codes::iterator it = codes.begin();
  while(it != codes.end())
  {
    parse(it->second);
    if (it->second.size() == 0)
    {
      codes.erase(it++);
      continue;
    }
    it++;
  }
}

void Formator::refresh(Codes &codes)
{
  Reader reader(_files);
  reader.scan(codes);
  format(codes);
}
