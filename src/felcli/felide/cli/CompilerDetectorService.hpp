
#ifndef __FELIDE_CLI_COMPILERDETECTOR_HPP__
#define __FELIDE_CLI_COMPILERDETECTOR_HPP__

#include <string>
#include <vector>
#include <felide/Version.hpp>

namespace felide {
    struct CompilerDescription {
        std::string key;
        std::string name;
        felide::Version version;
    };

    /**
    * @brief Detects some details from a certain compiler
    */
    class CompilerDetectorService {
    public:    
        virtual ~CompilerDetectorService();

        virtual CompilerDescription detect() const = 0;
    };
}

#endif
