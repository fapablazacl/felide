
#ifndef __BORC_CLI_PROJECTPRESENTER_HPP__
#define __BORC_CLI_PROJECTPRESENTER_HPP__

#include <string>

namespace borc {
    class Module;
    class Project;
    class Toolchain;
	class ProjectController {
	public:
		explicit ProjectController(Project *project, Toolchain *toolchain);

		~ProjectController();

		void build(const std::string &moduleName);

		void clean();

		void run();

	private:
		Project *project;
		Toolchain *toolchain;
	};
}

#endif 
