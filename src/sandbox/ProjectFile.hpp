
#ifndef __FELIDE_SANDBOX_PROJECTFILE_HPP__
#define __FELIDE_SANDBOX_PROJECTFILE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace felide {
    class Project;
    class ProjectFile {
    public:
        explicit ProjectFile(const Project *project, const std::string path) {
            m_project = project;
            m_path = path;
        }

        virtual ~ProjectFile() {}

        virtual const Project* getProject() const {
            return m_project;
        }

        virtual std::string getPath() const {
            return m_path;
        }

    private:
        const Project *m_project;
        std::string m_path;
    };
}

#endif
