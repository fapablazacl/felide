
#ifndef ___FELIDE_CLI_BORC_CLIBORCCONTROLLER_HPP__
#define ___FELIDE_CLI_BORC_CLIBORCCONTROLLER_HPP__

#include <string>
#include <vector>

namespace felide {
    class CompilerEnumeratorService;
    class CliBorcController {
    public:
        CliBorcController(CompilerEnumeratorService *compilerEnumeratorService);

        void dispatch(const std::string &subcommand, const std::vector<std::string> &params);

    private:
        void showHelp();

        void configure(const std::vector<std::string> &params);

        void build(const std::vector<std::string> &params);

    private:
        CompilerEnumeratorService *compilerEnumeratorService = nullptr;
    };
}

#endif
