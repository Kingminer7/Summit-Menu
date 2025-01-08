#include "../Hack.hpp"

namespace summit::hacks::config {
    class ShowBall : public summit::hacks::Hack {
        protected:
            bool toggled = false;
        public:
            ShowBall() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}