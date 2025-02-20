#pragma once

#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Geode/cocos/touch_dispatcher/CCTouch.h"
#include <functional>

namespace summit::ui {
  class MenuBall : public cocos2d::CCMenu {
  protected:
    static MenuBall *m_instance;

    bool m_handleTouch = true;
    bool m_render = true;
    bool m_moving = false;

    std::function<void()> m_callback;

    cocos2d::CCPoint *m_startPos;
    cocos2d::CCPoint m_diff;
    cocos2d::CCSprite *m_sprite;
    
    float m_scale = 1.0f;
    float m_multiplier = 0.8f;

    bool init() override;
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
    void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
    void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
    void ccTouchCancelled(cocos2d::CCTouch *touch,
                          cocos2d::CCEvent *event) override {
      ccTouchEnded(touch, event);
    }
    void registerWithTouchDispatcher() override;
  public:
    static MenuBall *get(bool createIfNone = false);
    void onPress();
    // void update(float dt) override;
    std::function<void()> getCallback();
    void setCallback(std::function<void()> callback);
    bool isRendered();
    void setRendered(bool render);
    bool isHandlingTouch();
    void setHandlingTouch(bool handle);
  };
}