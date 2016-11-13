#include <iostream>

#include "Rule.h"

#define COMMENT_SINGLE    "//"
#define COMMENT_BEGIN     "/*"
#define COMMENT_END       "*/"
#define COMMENT_SYMBOL_LEN 2

bool CommentRule::removeCommentLine(Text &text, Text::iterator &it)
{
  size_t pos = 0;
  if ((pos=it->str.find(COMMENT_SINGLE)) == std::string::npos)
    return false; 
  if (pos !=0)
  {
    it->str.erase(pos, std::string::npos);  
    return false;
  }
  text.erase(it++);
  return true;
}

void CommentRule::removeCommentBlock(Text &text, Text::iterator &it)
{
  size_t pos1 = 0, pos2 = 0;
  if ((pos1=it->str.find(COMMENT_BEGIN)) == std::string::npos)
  {
    it++;
    return;
  }
  if ((pos2=it->str.find(COMMENT_END)) != std::string::npos)
  {
    it->str.erase(pos1, pos2+COMMENT_SYMBOL_LEN-pos1);  
    it++;
    return;
  }
  it->str.erase(pos1, std::string::npos);  
  it++;
  while(it != text.end())
  {
    if ((pos2 = it->str.find(COMMENT_END)) != std::string::npos)
    {
      it->str.erase(0, pos2+COMMENT_SYMBOL_LEN);
      it++;
      break;
    }
    text.erase(it++);
  }
}

void CommentRule::handle(Text &text)
{
  Text::iterator it = text.begin();
  while(it != text.end())
  {
    if (removeCommentLine(text, it))
      continue;
    removeCommentBlock(text, it);
  }
}

void BlankRule::removeBlanks(std::string &str)
{
  int size = 0;
  for(size_t i = 0; i < str.length(); i++)
  {
    if((str[i] == ' ')  ||
       (str[i] == '\t') ||
       (str[i] == '\r') ||
       (str[i] == '\n'))
    {
      continue;
    }
    str[size++] = str[i];
  }
  str.erase(str.begin()+size, str.end());
}

void BlankRule::handle(Text &text)
{
  Text::iterator it = text.begin();
  while(it != text.end())
  {
    removeBlanks(it->str);
    if ((it->str).empty())
      it = text.erase(it);
    else
      it++;
  }
}

#define BRACE_START '{'
#define BRACE_END '}'

std::vector<std::string> BraceRule::seperateBraces(std::string &str)
{
  std::vector<std::string> multi;
  size_t pre = 0, cur = 0;
  std::string token;  

  for (cur = 0; cur < str.length(); cur++)
  {
    if ((str[cur] == BRACE_START) ||
        (str[cur] == BRACE_END)) 
    {
      token = str.substr(pre, cur-pre);  
      if (!token.empty())
      {
        multi.push_back(token); 
      }
      std::string brace(&str[cur], 1);
      multi.push_back(brace);
      pre = cur + 1;
    }
  }
  token = str.substr(pre, cur-pre);  
  if (!token.empty())
  {
    multi.push_back(token);
  }
  return multi;
}

void BraceRule::handle(Text &text)
{
  Text::iterator it = text.begin();
  while(it != text.end())
  {
    if ((it->str.find(BRACE_START) == std::string::npos) &&
        (it->str.find(BRACE_END) == std::string::npos))
    {
      it++;
      continue;
    }
    Line line;
    line.id = it->id;
    std::vector<std::string> multi;
    multi = seperateBraces(it->str);
    it = text.erase(it);
    for(std::string str : multi)
    {
      line.str = str;
      text.insert(it, line);
    }
  }
}
