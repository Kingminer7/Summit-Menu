#include "../../ui/UIManager.hpp"
#include "TextBypass.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::bypass {
    void TextBypass::init() {
        charLimitBypass = summit::Config::get<bool>("bypass.charlimit.toggled", false);
        charFilterBypass = summit::Config::get<bool>("bypass.charfilter.toggled", false);
        auto widget = ui::Widget::create("bypass.charlimit")
            ->addComponent(
                ui::Toggle::create("bypass.charlimit.toggle", charLimitBypass,
                    [this](ui::Component *comp, bool value) {
                        this->charLimitBypass = value;
                        summit::Config::set("bypass.charlimit.toggled", value);
                    }))
            ->addComponent(ui::Label::create("bypass.charlimit.label", "Character Limit Bypass"))
            ->setTab("Bypass");
        ui::registerWidget("CharLimitBypass", widget);
        widget = ui::Widget::create("bypass.charfilter")
            ->addComponent(
                ui::Toggle::create("bypass.charfilter.toggle", charFilterBypass,
                    [this](ui::Component *comp, bool value) {
                        this->charFilterBypass = value;
                        summit::Config::set("bypass.charfilter.toggled", value);
                    }))
            ->addComponent(ui::Label::create("bypass.charfilter.label", "Character Filter Bypass"))
            ->setTab("Bypass");
        ui::registerWidget("CharFilterBypass", widget);
    };

    std::string TextBypass::getId() {
        return "bypass.textbypass";
    };

    std::string TextBypass::getTab() {
        return "Bypass";
    };

    void TextBypass::update(float) {
        
    };

    RegisterHack(TextBypass)
}


#include <Geode/modify/CCTextInputNode.hpp>
class $modify (CCTextInputNode) {
    struct Fields {
        int m_origLength = 0;
        std::string m_origChars = "";
    };
    void updateLabel(std::string p0) {
        if (summit::Config::get<bool>("bypass.charlimit.enabled", false)) {
            if (m_maxLabelLength != 90831438) {
                m_fields->m_origLength = m_maxLabelLength;
                setMaxLabelLength(90831438);
            }
        } else if (m_maxLabelLength == 90831438) setMaxLabelLength(m_fields->m_origLength);

        if (summit::Config::get<bool>("bypass.charfilter.enabled", false)) {
            if (m_allowedChars != "`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ") {
                m_fields->m_origChars = m_allowedChars;
                setAllowedChars("`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ");
            }
        } else if (m_allowedChars == "`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ") setAllowedChars(m_fields->m_origChars);

        CCTextInputNode::updateLabel(p0);
    }
};