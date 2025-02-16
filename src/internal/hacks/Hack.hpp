#pragma once

#include <string>
namespace summit::hack {
class Hack {
  public:
    virtual std::string getId() = 0;
    virtual std::string getTab() = 0;

    virtual void update(float delta) {}
    virtual void init() = 0;

    virtual bool isCheat() { return true; }
};
}