#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

#include <string.h>

#include "Dir.h"

const std::string Dir::FILE_SUFFIX[] = {".c", ".h", ".cpp", ".hpp", ".cc"};

bool Dir::isSourceFile(std::string fileName)
{
  for(std::string  suffix : Dir::FILE_SUFFIX)
  {
    if (fileName.rfind(suffix) == (fileName.length() - suffix.length())) 
    {
      return true;
    }
  }
  return false;
}

Files & Dir::searchFiles(std::string dirName)
{
  DIR *dir;
  struct dirent *entry;
  struct stat fileAttr;
  if ((dir = opendir(dirName.c_str())) == NULL)
    return _files;
  while((entry = readdir(dir)) != NULL)
  {
    if ((strcmp(entry->d_name, ".") == 0) ||
        (strcmp(entry->d_name, "..") == 0))
      continue;
    if ((*dirName.rbegin()) == '/') 
      dirName.erase(dirName.length() - 1);
    std::string fullPath = dirName + "/" + entry->d_name;
    stat(fullPath.c_str(), &fileAttr);
    if (S_ISDIR(fileAttr.st_mode)) 
    {
      searchFiles(fullPath);
    }
    else if (isSourceFile(entry->d_name))
    {
      _files.push_back(fullPath);
    }
  }
  closedir(dir);
  return _files;
}
