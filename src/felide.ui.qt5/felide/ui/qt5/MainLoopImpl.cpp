
#include "MainLoopImpl.hpp"


namespace felide {
    MainLoopImpl::MainLoopImpl(int argc, char **argv) 
        : m_app(argc, argv) {}

    MainLoopImpl::~MainLoopImpl() {}

    int MainLoopImpl::run() {
        return m_app.exec();
    }
}
