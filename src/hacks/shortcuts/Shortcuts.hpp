#include "../Hack.hpp"

namespace summit::hacks::shortcuts {
    class Shortcuts : public summit::hacks::Hack {
        public:
            Shortcuts() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}