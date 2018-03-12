
#include <gtkmm.h>
#include <iostream>

#include <Felide/FileUtil.hpp>
#include <Felide/UI/GTK3/MainWindow.hpp>
#include <Felide/UI/GTK3/MainApplication.hpp>

int main(int argc, char* argv[]) {
    auto app = Felide::GTK3::MainApplication::create(argc, argv, "org.devwarecl.felide");

    Felide::GTK3::MainWindow window;
    return app->run(window);
}
