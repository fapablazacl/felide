
#ifndef __borc_moduletarget_hpp__
#define __borc_moduletarget_hpp__

#include <memory>
#include <vector>

#include "Target.hpp"

namespace borc {
    class Source;
    class Project;
    class Language;
    class Toolset;

    enum class ModuleTargetType;

    /**
     * @brief A target that generates executable modules, like a Program or a Library, independent of the programming language used
     */
    class ModuleTarget : public Target {
    public:
        friend class Project;

    public:
        virtual ~ModuleTarget() {}

        virtual ModuleTarget* setName(const std::string &name) override = 0;

        /**
         * @brief Get the current programming language used by this ModuleTarget
         */
        virtual Language* getLanguage() const = 0;

        /**
         * @brief Set the current programming language used by the current ModuleTarget
         */
        virtual ModuleTarget* setLanguage(Language *language) = 0;

        /**
         * @brief Set the path of the ModuleTarget
         */
        virtual ModuleTarget* setPath(const std::string &path)  = 0;

        /**
         * @brief Get the current path of the ModuleTarget
         */
        virtual std::string getPath() const = 0;

        /**
         * @brief Set the type of ModuleTarget
         */
        virtual ModuleTarget* setType(const ModuleTargetType type) = 0;

        /**
         * @brief Get the type of ModuleTarget
         */
        virtual ModuleTargetType getType() const = 0;
        
        /**
         * @brief Adds a new dependency to the target.
         */
        virtual ModuleTarget* addDependency(const Target *target)  = 0;

        /**
         * @brief Enumerate all the dependencies of the current module target
         */
        virtual std::vector<const Target*> getDependencies() const  = 0;

        /**
         * @brief Enumerate all the current source files 
         */
        virtual std::vector<Source> getSources() const  = 0;

    private:
        static std::unique_ptr<ModuleTarget> create(Project *project);
    };
}

#endif
