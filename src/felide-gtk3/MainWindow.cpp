
#include "MainWindow.hpp"
#include <iostream>

namespace felide {
    MainWindow::MainWindow() {
        m_sourceView.get_buffer()->set_text("This is a test!");
        m_sourceView.show();

        m_notebook.append_page(m_sourceView);
        this->set_border_width(10);

        /*
        m_button.signal_clicked().connect(
            sigc::mem_fun(
                *this, 
                &MainWindow::OnButtonClicked
            )
        );
        */
        this->add(m_notebook);

        m_notebook.show();
    }

    MainWindow::~MainWindow() {}

    void MainWindow::OnButtonClicked() {
        std::cout << "Hello, World!" << std::endl;
    }
}
