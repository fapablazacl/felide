
#include <gtkmm.h>
#include <felide/UI/GTK3/MainWindow.hpp>
#include <felide/UI/GTK3/MainApplication.hpp>

int main(int argc, char* argv[]) {
    using namespace felide::gtk3;

    auto window = MainWindow::create_raw();
    auto app = MainApplication::create(argc, argv, "org.devwarecl.felide");
    
    return app->run(*window);
}
