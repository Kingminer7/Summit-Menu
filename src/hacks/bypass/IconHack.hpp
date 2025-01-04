#include "../Hack.hpp"

namespace summit::hacks::bypass {
    class IconHack : public summit::hacks::Hack {
        protected:
            bool toggled = false;
        public:
            IconHack() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}