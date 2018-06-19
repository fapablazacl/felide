
#include "ProjectParserMock.hpp"

#include <borc/pom/Project.hpp>
#include <borc/pom/Target.hpp>
#include <borc/pom/Source.hpp>

namespace borc {
    std::unique_ptr<Project> ProjectParserMock::parse(const std::string &file) {
        auto borcProject = std::make_unique<borc::Project>("borc");
        
        auto borcTarget = borcProject->addTarget()
            ->setName("borc")
            ->setPath("src/borc")
            ->setType(borc::TargetType::Program);

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
            "borc/pom/Target.hpp",
            "borc/pom/Target.cpp",
            "borc/pom/Project.hpp",
            "borc/pom/Project.cpp",
            "borc/pom/Source.hpp",
            "borc/pom/Source.cpp",
            "borc/pom/ProjectParser.hpp",
            "borc/pom/ProjectParser.cpp",
            "borc/pom/ProjectParserMock.hpp",
            "borc/pom/ProjectParserMock.cpp",
            "borc/cpp/CppProject.hpp",
            "borc/cpp/CppProject.cpp"
        };

        for (const std::string &filePath : borcTargetSources) {
            borcTarget->addSource(filePath);
        }

        return borcProject;        
    }
}
