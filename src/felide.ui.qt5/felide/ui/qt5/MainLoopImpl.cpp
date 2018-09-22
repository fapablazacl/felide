
#include "MainLoopImpl.hpp"
#include <iostream>

namespace felide {
    MainLoopImpl::MainLoopImpl(int argc, char **argv) : m_app(argc, argv) {
        std::cout << argv[0] << std::endl;
    }

    MainLoopImpl::~MainLoopImpl() {}

    int MainLoopImpl::run() {
        return m_app.exec();
    }
}
