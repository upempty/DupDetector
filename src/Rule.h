#ifndef _RULE_H_
#define _RULE_H_

#include "CmdParser.h"
#include "Reader.h"

class Rule
{
public:
  virtual ~Rule() {};
  virtual void handle(Text &text) = 0; 
};

class CommentRule : public Rule
{
public:
  virtual ~CommentRule() {};
  virtual void handle(Text &text);
private:
  bool removeCommentLine(Text &text, Text::iterator &it);
  void removeCommentBlock(Text &text, Text::iterator &it);
};

class BlankRule : public Rule
{
public:
  virtual ~BlankRule() {};
  virtual void handle(Text &text);
private:
  void removeBlanks(std::string &str);
};

class BraceRule : public Rule
{
public:
  virtual ~BraceRule() {};
  void handle(Text &text);
private:
  std::vector<std::string> seperateBraces(std::string &str);
};

#endif
