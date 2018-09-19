
#ifndef __FELIDE_UI_MENU_HPP__
#define __FELIDE_UI_MENU_HPP__

#include <string>
#include <vector>
#include <functional>

namespace felide {
    enum class MenuKind {
        SubMenu,
        Action,
        Separator
    };

    struct Menu {
        std::string text;
        std::string shortcut;
        std::vector<Menu> childs;
        MenuKind kind;
        std::function<void()> callback;
        
        static Menu menuBar(const std::vector<Menu> &childs);

        static Menu menu(const std::string &text, const std::vector<Menu> &childs);

        static Menu action(const std::function<void()> &callback, const std::string &text, const std::string &shortcut="");

        static Menu separator();
    };
}

#endif
