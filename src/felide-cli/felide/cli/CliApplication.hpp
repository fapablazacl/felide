
#ifndef __felide_cli_cliapplication_hpp__
#define __felide_cli_cliapplication_hpp__

#include <memory>

namespace felide {
    class CliApplication {
    public:
        virtual ~CliApplication() {}

        virtual void run() = 0;
    
    public:
        static std::unique_ptr<CliApplication> create(int argc, char **argv);
    };
}

#endif
