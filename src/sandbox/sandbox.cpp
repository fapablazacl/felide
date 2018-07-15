
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Workspace.hpp"
#include "Project.hpp"
#include "ProjectFile.hpp"

namespace felide {
    class Compiler {
    public:
        virtual std::string computeTargetFileTitle(const ProjectFile *file) {
            return "";
        }

        void compile(const ProjectFile *file) {

        }

    private:
        std::string m_cmd;
    };

    class Linker {
    public:
        
    };

    class ToolSet {
    public:

    };
}

int main(int argc, char **argv) {
    auto felideWs = felide::Workspace{"/Users/fapablaza/Desktop/devwarecl/felide/"};
    auto sandboxProject = felideWs.addProject("src/sandbox/");
    sandboxProject->addFile("sandbox.cpp");
    sandboxProject->addFile("ProjectFile.cpp");
    sandboxProject->addFile("ProjectFile.hpp");
    sandboxProject->addFile("Project.cpp");
    sandboxProject->addFile("Project.hpp");
    sandboxProject->addFile("Workspace.cpp");
    sandboxProject->addFile("Workspace.hpp");
    
    return 0;
}
