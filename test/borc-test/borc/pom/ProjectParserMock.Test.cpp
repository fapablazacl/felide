
#include "ProjectParserMock.hpp"

#include <Felide/POM/Project.hpp>
#include <Felide/POM/Target.hpp>
#include <Felide/POM/Source.hpp>

namespace Felide {
    std::unique_ptr<Project> ProjectParserMock::parse(const std::string &file) {
        auto borcProject = std::make_unique<Felide::Project>("borc");
        
        auto borcTarget = borcProject->addTarget()
            ->setName("borc")
            ->setPath("src/borc")
            ->setType(Felide::TargetType::Program);

        std::vector<std::string> borcTargetSources = {
            "Program.cpp",
            "borc/Task.hpp",
            "borc/Task.cpp",
            "borc/CommandTask.hpp",
            "borc/CommandTask.cpp",
            "borc/TaskPerformer.hpp",
            "borc/TaskPerformer.cpp",
            "borc/SerialTaskPerformer.hpp",
            "borc/SerialTaskPerformer.cpp",
            "borc/FileTypeRegistry.hpp",
            "borc/FileTypeRegistry.cpp",
            "borc/POM/Target.hpp",
            "borc/POM/Target.cpp",
            "borc/POM/Project.hpp",
            "borc/POM/Project.cpp",
            "borc/POM/Source.hpp",
            "borc/POM/Source.cpp",
            "borc/POM/ProjectParser.hpp",
            "borc/POM/ProjectParser.cpp",
            "borc/POM/ProjectParserMock.hpp",
            "borc/POM/ProjectParserMock.cpp",
            "borc/cpp/CppProject.hpp",
            "borc/cpp/CppProject.cpp"
        };

        for (const std::string &filePath : borcTargetSources) {
            borcTarget->addSource(filePath);
        }

        return borcProject;        
    }
}
