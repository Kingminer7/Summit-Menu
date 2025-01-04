#include "../../ui/UIManager.hpp"
#include "../../ui/FontManager.hpp"
#include "Fonts.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::config {

    std::vector<std::string> Fonts::fonts = {
        "Alegreya",
        "Assistant",
        "Carme",
        "Lato",
        "Montserrat",
        "Nunito",
        "OpenSans",
        "OpenSansCondensed",
        "OpenSansSemiCondensed",
        "Poppins",
        "Roboto",
        "SourceCodePro",
        "Ubuntu"
    };

    std::map<std::string, std::vector<std::string>> styleMap = {
        {"Alegreya", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"Assistant", {"Bold", "ExtraBold", "ExtraLight", "Light", "Medium", "Regular", "SemiBold"}},
        {"Carme", {"Regular"}},
        {"Lato", {"Black", "BlackItalic", "Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Regular", "Thin", "ThinItalic"}},
        {"Montserrat", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic", "Thin", "ThinItalic"}},
        {"Nunito", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"OpenSans", {"Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"OpenSansCondensed", {"Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"OpenSansSemiCondensed", {"Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"Poppins", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic", "Thin", "ThinItalic"}},
        {"Roboto", {"Black", "BlackItalic", "Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "Thin", "ThinItalic"}},
        {"SourceCodePro", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic" }},
        {"Ubuntu", {"Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular"}}
    };

    std::map<std::string, std::pair<std::string, std::string>> fontDDFonts = {
        {"Alegreya", {"Alegreya", "Regular"}},
        {"Assistant", {"Assistant", "Regular"}},
        {"Carme", {"Carme", "Regular"}},
        {"Lato", {"Lato", "Regular"}},
        {"Montserrat", {"Montserrat", "Regular"}},
        {"Nunito", {"Nunito", "Regular"}},
        {"OpenSans", {"OpenSans", "Regular"}},
        {"OpenSansCondensed", {"OpenSansCondensed", "Regular"}},
        {"OpenSansSemiCondensed", {"OpenSansSemiCondensed", "Regular"}},
        {"Poppins", {"Poppins", "Regular"}},
        {"Roboto", {"Roboto", "Regular"}},
        {"SourceCodePro", {"SourceCodePro", "Regular"}},
        {"Ubuntu", {"Ubuntu", "Regular"}}
    };

    std::map<std::string, std::pair<std::string, std::string>> styleDDFonts = {
        {"Black", {"Carme", "Black"}},
        {"BlackItalic", {"Carme", "BlackItalic"}},
        {"Bold", {"Carme", "Bold"}},
        {"BoldItalic", {"Carme", "BoldItalic"}},
        {"ExtraBold", {"Carme", "ExtraBold"}},
        {"ExtraBoldItalic", {"Carme", "ExtraBoldItalic"}},
        {"ExtraLight", {"Carme", "ExtraLight"}},
        {"ExtraLightItalic", {"Carme", "ExtraLightItalic"}},
        {"Italic", {"Carme", "Italic"}},
        {"Light", {"Carme", "Light"}},
        {"LightItalic", {"Carme", "LightItalic"}},
        {"Medium", {"Carme", "Medium"}},
        {"MediumItalic", {"Carme", "MediumItalic"}},
        {"Regular", {"Carme", "Regular"}},
        {"SemiBold", {"Carme", "SemiBold"}},
        {"SemiBoldItalic", {"Carme", "SemiBoldItalic"}},
        {"Thin", {"Carme", "Thin"}},
        {"ThinItalic", {"Carme", "ThinItalic"}}
    };

    void Fonts::init() {
        font = summit::Config::get<std::string>("config.fonts.font", "Carme");
        style = summit::Config::get<std::string>("config.fonts.style", "Regular");
        if (styleMap[font].empty() || std::find(styleMap[font].begin(), styleMap[font].end(), style) == styleMap[font].end()) {
            style = "Regular";
        }
        for (auto& [id, font] : styleDDFonts) {
            font.first = this->font;
        }

        auto styleWidget = ui::Widget::create("Styles")
            ->addComponent(
                ui::Dropdown::create("style", styleMap[font], style,
                    [this](ui::Component *comp, std::string value) {
                        this->style = value;
                        summit::Config::set("config.fonts.style", value);
                        summit::ui::setFont(font, style);
                    })->setFonts(styleDDFonts))
                    ->addComponent(ui::Label::create("font-style-lab", "Font Style"))
            ->setTab("Config")
            ->setExclusivity(ui::Exclusivity::ImGui);
        auto fontWidget = ui::Widget::create("Fonts")
            ->addComponent(
                ui::Dropdown::create("font", fonts, font,
                    [this, styleWidget](ui::Component *comp, std::string value) {
                        this->font = value;
                        summit::Config::set("config.fonts.font", value);
                        if (styleMap.find(value) != styleMap.end()) {
                            if (auto dd = styleWidget->getComponentWithType<ui::Dropdown>("style")) {
                                dd->setOptions(styleMap[value]);
                                if (std::find(styleMap[value].begin(), styleMap[value].end(), style) != styleMap[value].end()) {
                                    dd->setSelected(style);
                                } else {
                                    dd->setSelected("Regular");
                                    summit::Config::set("config.fonts.style", "Regular");
                                    style = "Regular";
                                }
                            }
                        }
                        for (auto& [id, font] : styleDDFonts) {
                            font.first = value;
                        }
                        if (auto dd = styleWidget->getComponentWithType<ui::Dropdown>("style")) {
                            dd->setFonts(styleDDFonts);
                        }
                        summit::ui::setFont(font, style);
                    })->setFonts(fontDDFonts))
            ->addComponent(ui::Label::create("font-lab", "Font"))
            ->setTab("Config")
            ->setExclusivity(ui::Exclusivity::ImGui);
        ui::registerWidget("Styles", styleWidget);
        ui::registerWidget("Fonts", fontWidget);

        summit::ui::setFont(font, style);
    };

    std::string Fonts::getId() {
        return "config.fonts";
    };

    std::string Fonts::getTab() {
        return "Config";
    };

    void Fonts::update(float) {
        
    };

    RegisterHack(Fonts)
}