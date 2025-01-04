#include "../Hack.hpp"

namespace summit::hacks::bypass {
    class TextBypass : public summit::hacks::Hack {
        protected:
            bool charLimitBypass = false;
            bool charFilterBypass = false;
        public:
            TextBypass() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}