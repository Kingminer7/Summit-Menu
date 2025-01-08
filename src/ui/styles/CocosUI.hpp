#pragma once

#include "Style.hpp"
#include "../UIManager.hpp"

namespace summit::ui::styles {
    class CocosPopup : public Popup<> {
    protected:
        bool setup() override;
        static CocosPopup *create();
        CCMenu *tabBtnMenu;
        
        std::vector<ScrollLayer *> m_menus;
        std::vector<CCMenuItemSpriteExtra *> m_menuBtns;
        std::string m_currentTab;
    public:
        void show() override;
        static void open();
        static void destroy();
        static CocosPopup *get();
        void onTab(CCObject *sender);
        void onClose(CCObject *) override;
    };

    class CocosUI : public Style {
        protected:
            bool displayed = true;
            
        public:
            void init() override;
            std::string getId() override { return "CocosUI"; }
            BaseType getBaseStyle() override { return BaseType::Cocos; }
            void update(float) override;
            void show() override;
            void hide() override;
            void toggle() override;
            bool isVisible();
    };

    RegisterStyle(CocosUI)
}
