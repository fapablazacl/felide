
#include "ProjectParserMock.hpp"

#include <boost/filesystem.hpp>

#include <Felide/POM/Project.hpp>
#include <Felide/POM/Target.hpp>
#include <Felide/POM/ModuleTargetType.hpp>
#include <Felide/POM/ModuleTarget.hpp>
#include <Felide/POM/Source.hpp>

namespace Felide {
    std::unique_ptr<Project> ProjectParserMock::parse(const std::string &file) {
        namespace fs = boost::filesystem;

        auto borcProject = Felide::Project::create("borc");
        
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
