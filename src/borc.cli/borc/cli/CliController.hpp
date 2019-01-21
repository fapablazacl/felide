
#ifndef __BORC_CLI_CLICONTROLLER_HPP__
#define __BORC_CLI_CLICONTROLLER_HPP__

namespace borc {
    class Project;
    class Toolchain;
	class CliController {
	public:
		explicit CliController(Project *project, Toolchain *toolchain);

		~CliController();

		void build();

		void clean();

		void run();

	private:
		Project *project;
		Toolchain *toolchain;
	};
}

#endif 
