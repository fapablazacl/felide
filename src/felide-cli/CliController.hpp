
#ifndef __borc_consoleapp_hpp__
#define __borc_consoleapp_hpp__

#include <memory>
#include <vector>
#include <string>

namespace felide {
    class CliController {
    public:
        virtual ~CliController() {}

        virtual void build(const std::string &targetName) = 0;

        virtual void init() = 0;

        virtual void list() = 0;

    public:
        static std::unique_ptr<CliController> create(const std::string &path);
    };
}

#endif 
