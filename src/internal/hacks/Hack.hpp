#pragma once

namespace summit::hack {
class Hack {
protected:
  std::string id;
  std::string tab;

public:
  std::string getId();
  std::string getTab();
};
}