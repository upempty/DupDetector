#include "Dup.h"

Dup::Dup(DupOptions options)
{
  _formator = new Formator(options.dir, options.filter);
  _formator->refresh(_codes);
  _detector = new Detector(_codes, options.minDupLines);
  _outFile = options.jsonFile;
}

Dup::~Dup()
{
  delete _formator;
  delete _detector;
}

bool Dup::exec(void)
{
  _detector->findDup();
  _dupPairs = _detector->get();
  Serializer serializer(_dupPairs, _outFile);
  serializer.write();
  return true;
}
