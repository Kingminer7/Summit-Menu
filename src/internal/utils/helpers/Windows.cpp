#include "../KeybindManager.hpp"
#include <Geode/Geode.hpp>

#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/CCEGLView.hpp>

class $modify (KeybindEGLView, cocos2d::CCEGLView) {
  void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto res = summit::keybinds::KeybindManager::get()->checkBinds((summit::keybinds::Keys) key, (summit::keybinds::KeyStates) action, mods);
    if (!res)
    CCEGLView::onGLFWKeyCallback(window, key, scancode, action, mods);
  }
};

#endif