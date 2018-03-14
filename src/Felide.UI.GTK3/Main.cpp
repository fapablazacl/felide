
#include <gtkmm.h>
#include <Felide/UI/GTK3/MainWindow.hpp>
#include <Felide/UI/GTK3/MainApplication.hpp>

int main(int argc, char* argv[]) {
    using namespace Felide::GTK3;

    auto window = MainWindow::create_raw();
    auto app = MainApplication::create(argc, argv, "org.devwarecl.felide");
    
    return app->run(*window);
}
