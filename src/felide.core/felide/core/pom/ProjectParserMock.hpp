
#ifndef __borc_projectparsermock_hpp__
#define __borc_projectparsermock_hpp__

#include "ProjectParser.hpp"

namespace felide {
    class Project;
    class ProjectParserMock : public ProjectParser {
    public:
        virtual ~ProjectParserMock() {}

        virtual std::unique_ptr<Project> parse(const boost::filesystem::path &filePath) override;
    };    
}

#endif 
