#ifndef _DIR_H_
#define _DIR_H_

#include <string>
#include <vector>

typedef std::vector<std::string> Files;

class Dir
{
public:
  static const std::string FILE_SUFFIX[];
  Dir() {};
  ~Dir() {};
  Files &searchFiles(std::string dirName);

private:
  bool isSourceFile(std::string fileName);
  Files _files;
};

#endif
