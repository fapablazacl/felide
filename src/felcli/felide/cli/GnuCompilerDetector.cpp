
#include "GnuCompilerDetector.hpp"

#include <boost/process.hpp>
#include <boost/algorithm/string.hpp>

namespace felide {
    GnuCompilerDetector::~GnuCompilerDetector() {}

    CompilerDescription GnuCompilerDetector::detect() const {
        const std::vector<std::string> specLines = this->invokeGCCv();
        const CompilerDescription compilerDesc = this->createDescriptionFromSpecLines(specLines);

        return compilerDesc;
    }

    CompilerDescription GnuCompilerDetector::createDescriptionFromSpecLines(const std::vector<std::string> &specLines) const {
        CompilerDescription compilerDesc;

        compilerDesc.key = "gcc";
        compilerDesc.name = "GNU Compiler Collection";
        compilerDesc.version = this->parseVersion(specLines[6]);

        return compilerDesc;
    }

    std::vector<std::string> GnuCompilerDetector::invokeGCCv() const {
        boost::process::ipstream pipeStream;
        boost::process::child childProcess {"gcc -v", boost::process::std_err > pipeStream};

        std::string line;
        std::vector<std::string> specs;

        while (pipeStream && std::getline(pipeStream, line) && !line.empty()) {
            specs.push_back(line);
        }

        childProcess.wait();

        return specs;
    }

    std::string GnuCompilerDetector::parseProperty(const std::string &propertyLine) const {
        return propertyLine;
    }

    felide::Version GnuCompilerDetector::parseVersion(const std::string &versionLine) const {
        std::vector<std::string> parts;

        boost::split(parts, versionLine, boost::is_any_of(" "));

        return felide::Version::parse(parts[2]);
    }
}
