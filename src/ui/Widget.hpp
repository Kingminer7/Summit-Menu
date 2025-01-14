namespace summit::ui {
    class Widget {
        protected:
            std::string id;
        public:
            virtual void init() = 0;

            std::string getId();
    };
}