#include "../Hack.hpp"
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <ui/Widget.hpp>
#include <utils/Config.hpp>

namespace summit::hacks::level {
class $modify(AllPassGOHook, GameObject) {
  struct Fields {
    bool m_isPassable = false;
    bool m_checked = false;
  };
};

class $modify(AllPassPLHook, PlayLayer) {
  void setupHasCompleted() {
    PlayLayer::setupHasCompleted();
    for (auto obj : geode::cocos::CCArrayExt<AllPassGOHook *>(m_objects)) {
      auto fields = obj->m_fields.self();
      fields->m_isPassable = obj->m_isPassable;
      fields->m_checked = true;
      if (Config::get("level.allpassable.enabled", false)) obj->m_isPassable = true;
    }
  }
};

class SafeMode : public Hack {
public:
  void init() {
    ui::ToggleComponent::create(
        "level.allpassable", "All Passable",
        Config::get("level.allpassable.enabled", false),
        [](bool toggled) {
          if (auto pl = PlayLayer::get()) {
            for (auto obj :
                 geode::cocos::CCArrayExt<AllPassGOHook *>(pl->m_objects)) {
              auto fields = obj->m_fields.self();
              if (!fields->m_checked) {
                fields->m_isPassable = obj->m_isPassable;
                fields->m_checked = true;
              }
              obj->m_isPassable = toggled || fields->m_isPassable;
            }
          }
          Config::set("level.allpassable.enabled", toggled);
        })
        ->setTab("Level")
        ->reg();
  }

  std::string getId() { return "level.allpassable"; }
  std::string getTab() { return "Level"; }
};

RegisterHack(SafeMode)
} // namespace summit::hacks::level