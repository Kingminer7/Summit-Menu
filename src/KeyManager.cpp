#include "KeyManager.hpp"
#include "Summit.hpp"

namespace summit::utils {
std::vector<Keybind *> KeyManager::keybinds = {};

std::map<std::string, Key> KeyManager::getStringBinds() {
  return {
    {"A", Key::A},
    {"B", Key::B},
    {"C", Key::C},
    {"D", Key::D},
    {"E", Key::E},
    {"F", Key::F},
    {"G", Key::G},
    {"H", Key::H},
    {"I", Key::I},
    {"J", Key::J},
    {"K", Key::K},
    {"L", Key::L},
    {"M", Key::M},
    {"N", Key::N},
    {"O", Key::O},
    {"P", Key::P},
    {"Q", Key::Q},
    {"R", Key::R},
    {"S", Key::S},
    {"T", Key::T},
    {"U", Key::U},
    {"V", Key::V},
    {"W", Key::W},
    {"X", Key::X},
    {"Y", Key::Y},
    {"Z", Key::Z},
    {"Zero", Key::Zero},
    {"One", Key::One},
    {"Two", Key::Two},
    {"Three", Key::Three},
    {"Four", Key::Four},
    {"Five", Key::Five},
    {"Six", Key::Six},
    {"Seven", Key::Seven},
    {"Eight", Key::Eight},
    {"Nine", Key::Nine},
    {"Enter", Key::Enter},
    {"Space", Key::Space},
    {"Backspace", Key::Backspace},
    {"Tab", Key::Tab},
    {"CapsLock", Key::CapsLock},
    {"LeftShift", Key::LeftShift},
    {"RightShift", Key::RightShift},
    {"LeftControl", Key::LeftControl},
    {"RightControl", Key::RightControl},
    {"Alt", Key::Alt},
    {"LeftArrow", Key::LeftArrow},
    {"RightArrow", Key::RightArrow},
    {"UpArrow", Key::UpArrow},
    {"DownArrow", Key::DownArrow},
    {"Escape", Key::Escape},
    {"F1", Key::F1},
    {"F2", Key::F2},
    {"F3", Key::F3},
    {"F4", Key::F4},
    {"F5", Key::F5},
    {"F6", Key::F6},
    {"F7", Key::F7},
    {"F8", Key::F8},
    {"F9", Key::F9},
    {"F10", Key::F10},
    {"F11", Key::F11},
    {"F12", Key::F12},
    {"Tilde", Key::Tilde},
    {"Minus", Key::Minus},
    {"Equals", Key::Equals},
    {"LeftBracket", Key::LeftBracket},
    {"RightBracket", Key::RightBracket},
    {"Backslash", Key::Backslash},
    {"Semicolon", Key::Semicolon},
    {"Apostrophe", Key::Apostrophe},
    {"Comma", Key::Comma},
    {"Period", Key::Period},
    {"Slash", Key::Slash},
    {"NumPadZero", Key::NumPadZero},
    {"NumPadOne", Key::NumPadOne},
    {"NumPadTwo", Key::NumPadTwo},
    {"NumPadThree", Key::NumPadThree},
    {"NumPadFour", Key::NumPadFour},
    {"NumPadFive", Key::NumPadFive},
    {"NumPadSix", Key::NumPadSix},
    {"NumPadSeven", Key::NumPadSeven},
    {"NumPadEight", Key::NumPadEight},
    {"NumPadNine", Key::NumPadNine},
    {"Multiply", Key::Multiply},
    {"Add", Key::Add},
    {"Subtract", Key::Subtract},
    {"Decimal", Key::Decimal},
    {"Divide", Key::Divide},
    {"ScrollLock", Key::ScrollLock},
    {"Pause", Key::Pause},
    {"Insert", Key::Insert},
    {"Delete", Key::Delete},
    {"Home", Key::Home},
    {"End", Key::End},
    {"PageUp", Key::PageUp},
    {"PageDown", Key::PageDown},
    {"PrintScreen", Key::PrintScreen},
    {"LeftWindows", Key::LeftWindows},
    {"RightWindows", Key::RightWindows},
    {"Unknown", Key::Unknown},
  };
}

void KeyManager::addKeybind(Keybind *keybind) {
  keybind->key = (Key)summit::Config::get<int>("keybinds." + keybind->id,
                                               (int)keybind->key);
  keybinds.push_back(keybind);
}

void KeyManager::removeKeybind(std::string id) {
  keybinds.erase(
      std::remove_if(keybinds.begin(), keybinds.end(),
                     [id](Keybind *keybind) { return keybind->id == id; }),
      keybinds.end());
}

void KeyManager::clearKeybinds() { keybinds.clear(); }

Keybind *KeyManager::getKeybind(std::string id) {
  for (auto keybind : keybinds) {
    if (keybind->id == id) {
      return keybind;
    }
  }
  return nullptr;
}

std::vector<Keybind *> KeyManager::getKeybinds() { return keybinds; }

std::map<enumKeyCodes, Key> cocosKeys = {
    {enumKeyCodes::KEY_A, Key::A},
    {enumKeyCodes::KEY_B, Key::B},
    {enumKeyCodes::KEY_C, Key::C},
    {enumKeyCodes::KEY_D, Key::D},
    {enumKeyCodes::KEY_E, Key::E},
    {enumKeyCodes::KEY_F, Key::F},
    {enumKeyCodes::KEY_G, Key::G},
    {enumKeyCodes::KEY_H, Key::H},
    {enumKeyCodes::KEY_I, Key::I},
    {enumKeyCodes::KEY_J, Key::J},
    {enumKeyCodes::KEY_K, Key::K},
    {enumKeyCodes::KEY_L, Key::L},
    {enumKeyCodes::KEY_M, Key::M},
    {enumKeyCodes::KEY_N, Key::N},
    {enumKeyCodes::KEY_O, Key::O},
    {enumKeyCodes::KEY_P, Key::P},
    {enumKeyCodes::KEY_Q, Key::Q},
    {enumKeyCodes::KEY_R, Key::R},
    {enumKeyCodes::KEY_S, Key::S},
    {enumKeyCodes::KEY_T, Key::T},
    {enumKeyCodes::KEY_U, Key::U},
    {enumKeyCodes::KEY_V, Key::V},
    {enumKeyCodes::KEY_W, Key::W},
    {enumKeyCodes::KEY_X, Key::X},
    {enumKeyCodes::KEY_Y, Key::Y},
    {enumKeyCodes::KEY_Z, Key::Z},
    {enumKeyCodes::KEY_Zero, Key::Zero},
    {enumKeyCodes::KEY_One, Key::One},
    {enumKeyCodes::KEY_Two, Key::Two},
    {enumKeyCodes::KEY_Three, Key::Three},
    {enumKeyCodes::KEY_Four, Key::Four},
    {enumKeyCodes::KEY_Five, Key::Five},
    {enumKeyCodes::KEY_Six, Key::Six},
    {enumKeyCodes::KEY_Seven, Key::Seven},
    {enumKeyCodes::KEY_Eight, Key::Eight},
    {enumKeyCodes::KEY_Nine, Key::Nine},
    {enumKeyCodes::KEY_Enter, Key::Enter},
    {enumKeyCodes::KEY_Space, Key::Space},
    {enumKeyCodes::KEY_Backspace, Key::Backspace},
    {enumKeyCodes::KEY_Tab, Key::Tab},
    {enumKeyCodes::KEY_CapsLock, Key::CapsLock},
    {enumKeyCodes::KEY_LeftShift, Key::LeftShift},
    {enumKeyCodes::KEY_RightShift, Key::RightShift},
    {enumKeyCodes::KEY_LeftControl, Key::LeftControl},
    {enumKeyCodes::KEY_RightContol, Key::RightControl},
    {enumKeyCodes::KEY_ArrowLeft, Key::LeftArrow},
    {enumKeyCodes::KEY_ArrowRight, Key::RightArrow},
    {enumKeyCodes::KEY_ArrowUp, Key::UpArrow},
    {enumKeyCodes::KEY_ArrowDown, Key::DownArrow},
    {enumKeyCodes::KEY_Escape, Key::Escape},
    {enumKeyCodes::KEY_F1, Key::F1},
    {enumKeyCodes::KEY_F2, Key::F2},
    {enumKeyCodes::KEY_F3, Key::F3},
    {enumKeyCodes::KEY_F4, Key::F4},
    {enumKeyCodes::KEY_F5, Key::F5},
    {enumKeyCodes::KEY_F6, Key::F6},
    {enumKeyCodes::KEY_F7, Key::F7},
    {enumKeyCodes::KEY_F8, Key::F8},
    {enumKeyCodes::KEY_F9, Key::F9},
    {enumKeyCodes::KEY_F10, Key::F10},
    {enumKeyCodes::KEY_F11, Key::F11},
    {enumKeyCodes::KEY_F12, Key::F12},
    // {enumKeyCodes::KEY_TILDE, Key::Tilde}, // apparently cocos doesnt have
    // tilde
    {enumKeyCodes::KEY_OEMMinus, Key::Minus},
    // {enumKeyCodes::KEY_Equals, Key::Equals}, // doesnt have equals
    // {enumKeyCodes::KEY_LeftBracket, Key::LeftBracket}, // doenst have left
    // bracket {enumKeyCodes::KEY_RightBracket, Key::RightBracket}, // doesnt
    // have right bracket {enumKeyCodes::Backslash, Key::Backslash}, // doesnt
    // have backslash {enumKeyCodes::KEY_Semicolon, Key::Semicolon}, // doesnt
    // have semicolon {enumKeyCodes::KEY_Apostrophe, Key::Apostrophe}, // doesnt
    // have apostrophe
    {enumKeyCodes::KEY_OEMComma, Key::Comma},
    {enumKeyCodes::KEY_OEMPeriod, Key::Period},
    // {enumKeyCodes::KEY_Slash, Key::Slash}, // doesnt have slash
    {enumKeyCodes::KEY_NumPad0, Key::NumPadZero},
    {enumKeyCodes::KEY_NumPad1, Key::NumPadOne},
    {enumKeyCodes::KEY_NumPad2, Key::NumPadTwo},
    {enumKeyCodes::KEY_NumPad3, Key::NumPadThree},
    {enumKeyCodes::KEY_NumPad4, Key::NumPadFour},
    {enumKeyCodes::KEY_NumPad5, Key::NumPadFive},
    {enumKeyCodes::KEY_NumPad6, Key::NumPadSix},
    {enumKeyCodes::KEY_NumPad7, Key::NumPadSeven},
    {enumKeyCodes::KEY_NumPad8, Key::NumPadEight},
    {enumKeyCodes::KEY_NumPad9, Key::NumPadNine},
    {enumKeyCodes::KEY_Multiply, Key::Multiply},
    {enumKeyCodes::KEY_Add, Key::Add},
    {enumKeyCodes::KEY_Subtract, Key::Subtract},
    {enumKeyCodes::KEY_Decimal, Key::Decimal},
    {enumKeyCodes::KEY_Divide, Key::Divide},
    {enumKeyCodes::KEY_ScrollLock, Key::ScrollLock},
    {enumKeyCodes::KEY_Pause, Key::Pause},
    {enumKeyCodes::KEY_Insert, Key::Insert},
    {enumKeyCodes::KEY_Delete, Key::Delete},
    {enumKeyCodes::KEY_Home, Key::Home},
    {enumKeyCodes::KEY_End, Key::End},
    {enumKeyCodes::KEY_PageUp, Key::PageUp},
    {enumKeyCodes::KEY_PageDown, Key::PageDown},
    {enumKeyCodes::KEY_PrintScreen, Key::PrintScreen},
    {enumKeyCodes::KEY_LeftWindowsKey, Key::LeftWindows},
    {enumKeyCodes::KEY_RightWindowsKey, Key::RightWindows},
};

Key KeyManager::fromCocos(enumKeyCodes keyCode) {
  if (cocosKeys.find(keyCode) != cocosKeys.end())
    return cocosKeys[keyCode];
  else
    return Key::Unknown;
}

bool KeyManager::onPress(enumKeyCodes keyCode, bool repeat) {
  bool handled = false;
  auto key = fromCocos(keyCode);
  for (auto keybind : keybinds) {
    if (keybind->key == key) {
      keybind->callback(repeat);
      if (!keybind->passthrough)
        handled = true;
    }
  }
  return handled;
}

bool KeyManager::onPress(Key key, bool repeat) {
  bool handled = false;
  for (auto keybind : keybinds) {
    if (keybind->key == key) {
      keybind->callback(repeat);
      if (!keybind->passthrough)
        handled = true;
    }
  }
  return handled;
}

void KeyManager::loadBinds() {
  for (auto keybind : keybinds) {
    keybind->key = (Key)summit::Config::get<int>("keybinds." + keybind->id,
                                                 (int)keybind->key);
  }
}
} // namespace summit::utils

#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(cocos2d::CCKeyboardDispatcher) {
  bool dispatchKeyboardMSG(cocos2d::enumKeyCodes keyCode, bool isDown,
                           bool isRepeat) {
    if (isDown) {
      if (summit::utils::KeyManager::onPress(keyCode, isRepeat))
        return true;
    }
    return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(keyCode, isDown,
                                                              isRepeat);
  }
};