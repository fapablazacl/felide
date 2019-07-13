
#ifndef __FELIDE_CORE_POM_PROJECTPARSER_HPP__
#define __FELIDE_CORE_POM_PROJECTPARSER_HPP__

#include <memory>
#include <string>
#include <boost/filesystem/path.hpp>

namespace felide {
    class Project;
    class ProjectParser {
    public:
        virtual ~ProjectParser();

        virtual std::unique_ptr<Project> parse(const boost::filesystem::path &filePath) = 0;
    };    
}

#endif 
