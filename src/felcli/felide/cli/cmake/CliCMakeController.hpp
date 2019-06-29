
#ifndef __FELIDE_CLI_CLICMAKECONTROLLER_HPP__
#define __FELIDE_CLI_CLICMAKECONTROLLER_HPP__

#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>

namespace felide {
    class CompilerDetector;

    /**
    * @brief Controller that handles CMake projects.
    */
    class CliCMakeController {
    public:
        CliCMakeController(CompilerDetector *compilerDetector);

        void dispatch(const std::string &subcommand, const std::vector<std::string> &params);

    private:
        void showHelp();

        void configure(const std::vector<std::string> &params);

        void build(const std::vector<std::string> &params);

    private:
        bool isCMakeProject(const boost::filesystem::path &projectFolder) const;

        CompilerDetector *compilerDetector = nullptr;
    };
}

#endif
