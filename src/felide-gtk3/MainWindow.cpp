
#include "MainWindow.hpp"
#include <iostream>

namespace felide {
    MainWindow::MainWindow() : m_button("Hello World!") {
        this->set_border_width(10);

        m_button.signal_clicked().connect(
            sigc::mem_fun(
                *this, 
                &MainWindow::OnButtonClicked
            )
        );

        this->add(m_button);

        m_button.show();
    }

    MainWindow::~MainWindow() {}

    void MainWindow::OnButtonClicked() {
        std::cout << "Hello, World!" << std::endl;
    }
}
