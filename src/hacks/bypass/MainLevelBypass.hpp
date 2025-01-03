#include "../Hack.hpp"

namespace summit::hacks::global {
    class MainLevelBypass : public summit::hacks::Hack {
        protected:
            bool toggled = false;
        public:
            MainLevelBypass() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}