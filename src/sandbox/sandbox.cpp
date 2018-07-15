
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

        virtual std::string getFullPath() const {
            return m_path;
        }

    private:
        const Project *m_project;
        std::string m_path;
    };

    class Workspace;
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

        virtual std::string getFullPath() const {
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
            auto it = std::find_if(std::begin(m_files), std::end(m_files), [file](std::unique_ptr<ProjectFile> &filePtr) {
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

    class Workspace {
    public:
        explicit Workspace(const std::string path) {
            m_path = path;
        }

        virtual ~Workspace() {}

        virtual std::string getFullPath() const {
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
            auto it = std::find_if(std::begin(m_projects), std::end(m_projects), [project](std::unique_ptr<Project> &projectPtr) {
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

namespace felide {
    class Compiler {
    public:
        virtual std::string computeTargetFileTitle(const ProjectFile *file) {

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

    return 0;
}
