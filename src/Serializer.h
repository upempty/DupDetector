#ifndef _SERIALIZER_H_
#define _SERIALIZER_H_

#include "Detector.h"
#include "Output.h"

enum FormatType
{
  CONSOLE = 0,
  JSON    = 1,
};

class Serializer
{
public:
  virtual ~Serializer() {};
  Serializer(DupPairs &dupPairs, std::string jsonFile);
  std::string & write(void); 

private:
  static void initFormats(DupPairs &dupPairs);

private:
  std::string _file;
  FormatType _formatType;
  Output *_outFormat;
  std::string _output;
  std::ofstream _of;
};

#endif
