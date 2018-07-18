
#ifndef __FELIDE_TOOLSETS_COMPILERDESCRIPTION_HPP__
#define __FELIDE_TOOLSETS_COMPILERDESCRIPTION_HPP__

#include <string>
#include <vector>
#include <map>

namespace felide {
    struct CompilerDescription {
        std::string compileTemplate;
        std::vector<std::string> inputExtensions;
        std::string outputExtension;

        //! Map from VariableKey to specific compiler option
        std::map<std::string, std::string> keyOptionMap;
    };
}

#endif
