
#include <gtkmm.h>

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.devware.felide");

    Gtk::Window window;

    window.set_default_size(200, 200);

    return app->run(window);
}
