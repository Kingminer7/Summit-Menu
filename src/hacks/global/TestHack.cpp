#include "../Hack.hpp"

namespace summit::hacks::global {
  class TestHack : public Hack {
    public:
      void init() {

      }
      void update(float dt) {

      }

      std::string getId() {
          return "testhack";
      }
      std::string getTab() {
        return "Global";
      }
  };
}