#ifndef _DUP_H_
#define _DUP_H_

#include "CmdParser.h"
#include "Formator.h"
#include "Detector.h"
#include "Serializer.h"

class Dup
{
public:
  Dup(DupOptions options);
  ~Dup();
  bool exec(void);

private:
  Codes _codes;
  DupPairs _dupPairs;
  std::string _outFile;

  Formator *_formator;
  Detector *_detector;
  Serializer *_serializer;
};

#endif
