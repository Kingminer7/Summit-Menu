using namespace geode::prelude;

namespace summit::utils {
    // all keyboard keys
    enum class Key {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Zero,
        Enter,
        Space,
        Backspace,
        Tab,
        CapsLock,
        LeftShift,
        RightShift,
        LeftControl,
        RightControl,
        Alt,
        LeftArrow,
        RightArrow,
        UpArrow,
        DownArrow,
        Escape,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Tilde,
        Minus,
        Equals,
        LeftBracket,
        RightBracket,
        Backslash,
        Semicolon,
        Apostrophe,
        Comma,
        Period,
        Slash,
        NumPadZero,
        NumPadOne,
        NumPadTwo,
        NumPadThree,
        NumPadFour,
        NumPadFive,
        NumPadSix,
        NumPadSeven,
        NumPadEight,
        NumPadNine,
        Multiply,
        Add,
        Subtract,
        Decimal,
        Divide,
        ScrollLock,
        Pause,
        Insert,
        Delete,
        Home,
        End,
        PageUp,
        PageDown,
        PrintScreen,
        LeftWindows,
        RightWindows,
        Unknown,
    };

    struct Keybind {
        std::string id;
        std::string name;
        Key key;
        std::function<void(bool isRepeat)> callback;
        bool passthrough = false;
    };

    class KeyManager {
        protected:
            static std::vector<Keybind *> keybinds;
        public:
            static std::map<std::string, Key> getStringBinds();
            static void addKeybind(Keybind *keybind);
            static void removeKeybind(std::string id);
            static void clearKeybinds();
            static Keybind *getKeybind(std::string id);
            static std::vector<Keybind *> getKeybinds();
            static Key fromCocos(cocos2d::enumKeyCodes code);
            static bool onPress(cocos2d::enumKeyCodes code, bool repeat);
            static bool onPress(Key key, bool repeat);
            static void loadBinds();
    };
}