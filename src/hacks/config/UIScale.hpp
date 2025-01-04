#include "../Hack.hpp"

namespace summit::hacks::config {
    class UIScale : public summit::hacks::Hack {
        protected:
            float value = 1.0f;
        public:
            UIScale() {};
            
            void init() override;
            std::string getId() override;
            std::string getTab() override;
            void update(float) override;
    };
}