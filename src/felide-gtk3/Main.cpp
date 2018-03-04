
#include <gtkmm.h>
#include <iostream>

#include <felide/FileUtil.hpp>

#include "MainWindow.hpp"
#include "MainApplication.hpp"

int main(int argc, char* argv[]) {
    auto app = Felide::GTK3::MainApplication::create(argc, argv, "org.devwarecl.felide");

    Felide::GTK3::MainWindow window;
    return app->run(window);
}
