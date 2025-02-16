#pragma once

namespace summit::hack {
class Hack {
  protected:
    std::string id;
    std::string tab;

  public:
    virtual std::string getId() = 0;
    virtual std::string getTab() = 0;

    virtual void update(float delta) {};
    virtual void init() = 0;
};
}