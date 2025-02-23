#include <list>
#include <map>
#include <string>
namespace summit::ui {

  class Widget;
  class Tab;

  class UIManager {
    protected:
      static UIManager *m_instance;

      std::map<std::string, Tab *> m_tabs = {};
      std::list<std::string> m_order = {};

    public:
      static UIManager *get();

      void registerTab(Tab *tab);
      Tab *getTab(std::string id);
      std::list<std::string> getOrder();
      std::map<std::string, Tab *> getTabs();
  };

  class Tab {
    protected:
      Tab(){};
      std::list<std::string> m_order = {};
      std::map<std::string, Widget *> m_widgets = {};
      std::string m_id;
      void init(std::string id);
    public:
      std::string getId();
      std::list<std::string> getOrder();
      std::map<std::string, Widget *> getWidgets();
      Widget *getWidget(std::string id);
      void addWidget(Widget *widget);
      void removeWidget(std::string id);

      static Tab *create(std::string id);
      
  };

  class Widget {
    protected:
      Tab *m_tab = nullptr;
      std::string m_id = "";
      std::string m_label = "";
      virtual void init(std::string id, std::string label);
    public:
      std::string getId();
      std::string getLabel();
      auto *setLabel(std::string label);

      static Widget *create(std::string id, std::string label);
  };
}