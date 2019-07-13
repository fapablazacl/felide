
#ifndef __FELIDE_CORE_POM_PROJECTPARSERJSON_HPP__
#define __FELIDE_CORE_POM_PROJECTPARSERJSON_HPP__

#include "ProjectParser.hpp"

namespace felide {
    class Project;
    class ProjectParserJson : public ProjectParser {
    public:
        virtual ~ProjectParserJson();

        virtual std::unique_ptr<Project> parse(const boost::filesystem::path &filePath) override;
    };    
}

#endif 
