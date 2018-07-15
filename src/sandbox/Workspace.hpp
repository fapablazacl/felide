
#ifndef __FELIDE_SANDBOX_WORKSPACE_HPP__
#define __FELIDE_SANDBOX_WORKSPACE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Project.hpp"

namespace felide {
    class Project;
    class Workspace {
    public:
        explicit Workspace(const std::string path) {
            m_path = path;
        }

        virtual ~Workspace() {}

        virtual std::string getRootPath() const {
            return m_path;
        }

        virtual int getProjectCount() const {
            return m_projects.size();
        }

        virtual Project* getProject(const int index) const {
            return m_projects[index].get();
        }

        Project* addProject(const std::string &path) {
            auto project = new Project(this, path);

            m_projects.emplace_back(project);

            return project;
        }

        void destroyProject(Project *project) {
            auto it = std::find_if(std::begin(m_projects), std::end(m_projects), [project](auto &projectPtr) {
                return project == projectPtr.get();
            });

            if (it != std::end(m_projects)) {
                m_projects.erase(it);
            }
        }

    private:
        std::string m_path;
        std::vector<std::unique_ptr<Project>> m_projects;
    };
}

#endif
