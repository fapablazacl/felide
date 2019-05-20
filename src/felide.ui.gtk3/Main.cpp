
#include <gtkmm.h>
#include <felide/ui/gtk3/IDEFrameGtk.hpp>
#include <felide/ui/gtk3/MainApplication.hpp>

#include <memory>
#include <iostream>

int main(int argc, char* argv[]) {
    using namespace felide::gtk3;

    std::cout << "Initializing Application ..." << std::endl;
    auto app = MainApplication::create(argc, argv, "org.devwarecl.felide");
    std::cout << "Done." << std::endl;

    std::cout << "Initializing IDEFrameGtk ..." << std::endl;
    IDEFrameGtk window;
    std::cout << "Done." << std::endl;

    std::cout << "Running ..." << std::endl;

    return app->run(window);
}
