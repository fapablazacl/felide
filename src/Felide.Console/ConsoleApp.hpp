
#ifndef __borc_consoleapp_hpp__
#define __borc_consoleapp_hpp__

#include <memory>
#include <vector>
#include <string>

namespace borc {
    class ConsoleApp {
    public:
        virtual ~ConsoleApp() {}

        virtual void build(const std::string &targetName) = 0;

        virtual void init() = 0;

        virtual void list() = 0;

    public:
        static std::unique_ptr<ConsoleApp> create(const std::string &path);
    };
}

#endif 
