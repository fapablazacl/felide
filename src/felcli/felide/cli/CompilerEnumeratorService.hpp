
#ifndef __FELIDE_CLI_COMPILERENUMERATORSERVICE_HPP__
#define __FELIDE_CLI_COMPILERENUMERATORSERVICE_HPP__

#include <string>
#include <vector>

#include "CompilerDetectorService.hpp"

namespace felide {

    /**
    * @brief Detects some details from a certain compiler
    */
    class CompilerEnumeratorService {
    public:    
        std::vector<CompilerDescription> enumerate() const;
    };
}

#endif
