
#include <gtkmm/main.h>

#include <felide/gui/ide-frame/IDEFrameModel.hpp>
#include <felide/gui/ide-frame/IDEFramePresenter.hpp>
#include <felide/gui/gtk3/IDEFrameGtk.hpp>
#include <felide/gui/gtk3/MainApplication.hpp>

#include <memory>
#include <iostream>

int main(int argc, char* argv[]) {
    using namespace felide;
    using namespace felide::gtk3;

    std::cout << "Initializing Application ..." << std::endl;
    auto app = MainApplication::create(argc, argv, "org.devwarecl.felide");
    std::cout << "Done." << std::endl;

    std::cout << "Initializing IDEFrameGtk ..." << std::endl;
    auto model = IDEFrameModel::create();
    auto presenter = IDEFramePresenter{model.get()};
    auto window = IDEFrameGtk{&presenter};
    std::cout << "Done." << std::endl;

    std::cout << "Running ..." << std::endl;

    return app->run(window);
}
