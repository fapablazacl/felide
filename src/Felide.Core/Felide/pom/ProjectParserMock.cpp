
#include "ProjectParserMock.hpp"

#include <boost/filesystem.hpp>

#include <borc/pom/Project.hpp>
#include <borc/pom/Target.hpp>
#include <borc/pom/ModuleTargetType.hpp>
#include <borc/pom/ModuleTarget.hpp>
#include <borc/pom/Source.hpp>

namespace borc {
    std::unique_ptr<Project> ProjectParserMock::parse(const std::string &file) {
        namespace fs = boost::filesystem;

        auto borcProject = borc::Project::create("borc");
        
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
