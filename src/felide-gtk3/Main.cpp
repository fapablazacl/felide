
#include "MainWindow.hpp"
#include <gtkmm/application.h>

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.devware.felide");

    felide::MainWindow window;

    return app->run(window);
}
