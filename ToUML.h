#ifndef BEROEPSPRODUCT_TO_UML_H
#define BEROEPSPRODUCT_TO_UML_H

#include <fstream>
#include <list>
#include <map>
#include <memory>

class ToUML {
private:
  std::fstream mFileStream;

public:
  ToUML(const std::string &aFileName);

  void Render(const std::map<unsigned long, std::shared_ptr<class Machine>> &aMachines,
              std::list<std::shared_ptr<class Task>> aTasks);
};

#endif
