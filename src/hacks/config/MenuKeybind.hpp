#include "../Hack.hpp"
#include "../../KeyManager.hpp"

namespace summit::hacks::config {
    class MenuKeybind : public summit::hacks::Hack {
        public:
            MenuKeybind() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}