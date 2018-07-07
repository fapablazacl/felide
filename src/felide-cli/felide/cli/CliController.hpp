
#ifndef __felide_cli_clicontroller_hpp__
#define __felide_cli_clicontroller_hpp__

#include <memory>
#include <vector>
#include <string>

namespace felide {
    class CliController {
    public:
        virtual ~CliController() {}

        virtual void build() = 0;

        virtual void init() = 0;

        virtual void list() = 0;

    public:
        static std::unique_ptr<CliController> create();
    };
}

#endif 
