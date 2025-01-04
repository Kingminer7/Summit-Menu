#include "../Hack.hpp"

namespace summit::hacks::config {
    class Fonts : public summit::hacks::Hack {
        protected:
            std::string font = "Carme";
            std::string style = "Regular";
            static std::vector<std::string> fonts;
            static std::vector<std::string> styles;
        public:
            Fonts() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}