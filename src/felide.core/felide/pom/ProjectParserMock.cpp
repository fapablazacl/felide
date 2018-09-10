
#include "ProjectParserMock.hpp"

#include <boost/filesystem.hpp>

#include <felide/pom/Project.hpp>
#include <felide/pom/Target.hpp>
#include <felide/pom/ModuleTargetType.hpp>
#include <felide/pom/ModuleTarget.hpp>
#include <felide/pom/Source.hpp>

namespace felide {
    std::unique_ptr<Project> ProjectParserMock::parse(const std::string &file) {
        namespace fs = boost::filesystem;

        auto borcProject = felide::Project::create("borc");
        
#if defined(CMAKE_SOURCE_DIR)
        borcProject->setPath(BOOST_STRINGIZE(CMAKE_SOURCE_DIR));
#endif

        auto borcTarget = borcProject->createTarget<ModuleTarget>()
            ->setName("borc")
            ->setPath("src/borc")
            ->setType(ModuleTargetType::Program);

        auto borcCoreTarget = borcProject->createTarget<ModuleTarget>()
            ->setName("borc-core")
            ->setPath("src/borc-core")
            ->setType(ModuleTargetType::Library);

        return borcProject;
    }
}
