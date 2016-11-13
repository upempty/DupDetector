#include "Dup.h"

#ifndef __UT__
int main(int argc, char *argv[])
{
  try
  {
    DupOptions options;
    CmdParser cmdParser(argc, argv);  
    cmdParser.get(options);
    Dup dup(options);
    dup.exec();
  }
  catch(const std::exception & err)
  {
    std::cerr<<err.what()<<std::endl;
  }
  catch(...)
  {
    std::cerr<<"Unknown error"<<std::endl;
  }

  return 0;
}
#endif
