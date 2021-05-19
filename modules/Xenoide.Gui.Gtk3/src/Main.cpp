
#include <gtkmm/main.h>

#include <Xenoide/Gui/Gtk3/IDEFrameGtk.hpp>
#include <Xenoide/Gui/Gtk3/MainApplication.hpp>

#include <memory>
#include <iostream>

int main(int argc, char* argv[]) {
    using namespace Xenoide;

    std::cout << "Initializing Application ..." << std::endl;
    auto app = MainApplication::create(argc, argv, "org.devwarecl.Xenoide");
    std::cout << "Done." << std::endl;

    std::cout << "Initializing IDEFrameGtk ..." << std::endl;
    auto model = IDEFrame::Model::create();
    auto presenter = IDEFrame::Presenter{model.get()};
    auto window = IDEFrameGtk{&presenter};
    std::cout << "Done." << std::endl;

    std::cout << "Running ..." << std::endl;

    return app->run(window);
}
