
#ifndef __FELIDE_CLI_GNUCOMPILERDETECTOR_HPP__
#define __FELIDE_CLI_GNUCOMPILERDETECTOR_HPP__

#include "CompilerDetector.hpp"

#include <string>
#include <vector>

namespace felide {
    class GnuCompilerDetector : public CompilerDetector {
    public:
        virtual ~GnuCompilerDetector();

        virtual CompilerDescription detect() const override;
        
    private:
        CompilerDescription createDescriptionFromSpecLines(const std::vector<std::string> &specLines) const;

        std::vector<std::string> invokeGCCv() const;

        std::string parseProperty(const std::string &propertyLine) const;

        felide::Version parseVersion(const std::string &versionLine) const;
    };
}

#endif
