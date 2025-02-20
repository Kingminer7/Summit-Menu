// #include "KeybindManager.hpp"
// #include "Geode/loader/Log.hpp"

// namespace summit::keybinds {
//   void Keybind::init(std::string id, std::string name, Keys key, KeyStates state, std::list<Modifiers> modifiers) {
//     m_id = id;
//     m_name = name;
//     m_key = key;
//     m_state = state;
//     m_modifiers = modifiers;
//   }

//   Keybind *Keybind::create(std::string id, std::string name, Keys key, KeyStates state, std::list<Modifiers> modifiers) {
//     auto ret = new Keybind();
//     ret->init(id, name, key, state, modifiers);
//     return ret;
//   }

//   Keybind *Keybind::setKey(Keys key) {
//     m_key = key;
//     return this;
//   }

//   Keys Keybind::getKey() {
//     return m_key;
//   }


//   KeybindManager *KeybindManager::m_instance = nullptr;

//   KeybindManager *KeybindManager::get() {
//     if (!m_instance) m_instance = new KeybindManager;
//     return m_instance;
//   }
      
//   void KeybindManager::registerKeybind(Keybind bind) {
//     if (m_keybinds.contains(bind.id)) return geode::log::error("(KeybindManager) {} is already registered!", bind.id);
//     m_keybinds[bind.id] = bind;
//   }
//   void KeybindManager::removeKeybind(std::string id) {
//     if (!m_keybinds.contains(id)) return geode::log::error("(KeybindManager) {} is not registered!", id);
//     m_keybinds.erase(id);
//   }
//   Keybind KeybindManager::getKeybind(std::string id) {
//     return m_keybinds[id];
//   }
//   std::map<std::string, Keybind> KeybindManager::getKeybinds() {
//     return m_keybinds;
//   }
// }

// #include <Geode/modify/CCEGLView.hpp>
// class $modify (MyCCEGLView, cocos2d::CCEGLView) {
//   void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     // if (key == (int) Keys::Tab && action == (int) KeyStates::Press) return summit::ui::StyleManager::get()->getCurrentStyle()->toggle();
//     CCEGLView::onGLFWKeyCallback(window, key, scancode, action, mods);
//   }
// };