
#ifndef __borc_projectparseryaml_hpp__
#define __borc_projectparseryaml_hpp__

#include "ProjectParser.hpp"

namespace borc {
    class Project;
    class ProjectParserYaml : public ProjectParser {
    public:
        virtual ~ProjectParserYaml() {}

    public:
        static std::unique_ptr<ProjectParserYaml> create();
    };    
}

#endif 
