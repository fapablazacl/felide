
#include <cassert>
#include <felide/Core.hpp>
#include <felide/gui/UIToolkit.hpp>
#include <felide/core/system/PluginManager.hpp>

#include <iostream>

extern int felide_main(int argc, char **argv);

int main(int argc, char **argv) {
    return felide_main(argc, argv);

    /*
    auto core = std::make_unique<felide::Core>();
    auto pluginManager = core->getPluginManager();

    pluginManager->loadPlugin("felide.ui.qt5");

    auto toolkit = core->getToolkit();

    if (toolkit) {
        return toolkit->runApp(argc, argv);
    } else {
        std::cout << "felide: No UI Toolkit found" << std::endl;
        return 0;
    }
    */
}
