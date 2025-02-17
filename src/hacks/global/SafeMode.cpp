#include "Config.hpp"
#include "Geode/binding/GameStatsManager.hpp"
#include "ui/UIManager.hpp"
#include "ui/widgets/ToggleWidget.hpp"
#include <hacks/Hack.hpp>
#include <LoadManager.hpp>
#include <Geode/modify/PlayLayer.hpp>

namespace summit::hack::global {
  class SafeMode : Hack {
    public:
      std::string getTab() override { return "global"; }
      std::string getId() override { return "global.safemode"; }
      void init() override {
        geode::log::info("Registering safe mode: {}", ui::UIManager::registerWidget("Global", ui::widgets::ToggleWidget::create(getId(), "Safe Mode", Config::get<bool>("global.safemode", false))->setDescription("Prevents you from beating any levels.")->setCallback([](bool toggled) {
          Config::set<bool>("global.safemode", toggled);
        })));
      }
  };

  // class AutoSafeMode : Hack {
  //   public:
  //     std::string getTab() override { return "global"; }
  //     std::string getId() override { return "global.autosafemode"; }
  //     void init() override {
  //       ui::UIManager::registerWidget(getId(), ui::widgets::ToggleWidget::create(getId(), "Auto Safe Mode", false)->setDescription("Prevents you from beating any levels if you have any cheats enabled."));
  //     }
  // };

  class $modify(SMPlayLayer, PlayLayer) {
    struct Fields {
      int m_jumps;
      int m_attempts;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
      auto man = GameStatsManager::get();
      m_jumps = man->getStat("1");
      m_attempts = man->getStat("2");
      return PlayLayer::init(level, useReplay, dontCreateObjects);
    }

    void levelComplete() {
      bool sm = summit::Config::get<bool>("global.safemode", true);
      if (summit::Config::get<bool>("global.safemode", true)) {
        auto orig = m_isTestMode;
        m_isTestMode = true;
        PlayLayer::levelComplete();
        m_isTestMode = orig;
      } else PlayLayer::levelComplete();
    }

    void destroyPlayer(PlayerObject *p, GameObject *g) {
      if (summit::Config::get<bool>("global.safemode", true)) {
        auto orig = m_isTestMode;
        m_isTestMode = true;
        PlayLayer::destroyPlayer(p,g);
        m_isTestMode = orig;
        auto man = GameStatsManager::get();
        man->setStat("1", m_jumps);
        man->setStat("2", m_attempts);
      } else PlayLayer::destroyPlayer(p,g);
    }
  };

  $execute {
    LoadManager::onLoad([](){
      (new SafeMode)->init();
    },0,LoadTime::Early);
  }
}
