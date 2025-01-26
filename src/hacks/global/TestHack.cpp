#include "../Hack.hpp"
#include <ui/Widget.hpp>

namespace summit::hacks::global {
  class TestHack : public Hack {
    public:
      void init() {
        ui::Widget::create("TestWidget", 
        ui::ToggleComponent::create("test", "Test label", false, [](bool toggled){
          
        }))
        ->registerWidget("Global");
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

  RegisterHack(TestHack)
}