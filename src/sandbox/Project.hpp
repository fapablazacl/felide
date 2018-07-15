
/*
#ifndef __FELIDE_SANDBOX_PROJECT_HPP__
#define __FELIDE_SANDBOX_PROJECT_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ProjectFile.hpp"

namespace felide {
    class Workspace;
    class ProjectFile;
    class Project {
    public:
        explicit Project(const Workspace *workspace, const std::string path) {
            m_workspace = workspace;
            m_path = path;
        }

        virtual ~Project() {}

        virtual const Workspace* getWorkspace() const {
            return m_workspace;
        }

        virtual std::string getPath() const {
            return m_path;
        }

        virtual int getFileCount() const {
            return m_files.size();
        }

        virtual ProjectFile* getFile(const int index) const {
            return m_files[index].get();
        }

        ProjectFile* addFile(const std::string &path) {
            auto file = new ProjectFile(this, path);

            m_files.emplace_back(file);

            return file;
        }

        void destroyFile(ProjectFile *file) {
            auto it = std::find_if(std::begin(m_files), std::end(m_files), [file](auto &filePtr) {
                return file == filePtr.get();
            });

            if (it != std::end(m_files)) {
                m_files.erase(it);
            }
        }

    private:
        const Workspace *m_workspace;
        std::vector<std::unique_ptr<ProjectFile>> m_files;
        std::string m_path;
    };
}

#endif
*/