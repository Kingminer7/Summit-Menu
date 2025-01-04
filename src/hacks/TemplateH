#include "../Hack.hpp"

namespace summit::hacks::global {
    class TestHack : public summit::hacks::Hack {
        protected:
            bool toggled = false;
            float value = 1.0f;
        public:
            TestHack() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}