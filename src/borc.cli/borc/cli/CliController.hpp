
#ifndef __BORC_CLI_CLICONTROLLER_HPP__
#define __BORC_CLI_CLICONTROLLER_HPP__

#include <string>

namespace borc {
    class Module;
    class Project;
    class Toolchain;
	class CliController {
	public:
		explicit CliController(Project *project, Toolchain *toolchain);

		~CliController();

		void build(const std::string &moduleName);

		void clean();

		void run();

	private:
		Project *project;
		Toolchain *toolchain;
	};
}

#endif 
