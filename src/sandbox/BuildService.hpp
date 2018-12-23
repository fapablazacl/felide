
#ifndef __BORC_MODEL_BUILDSERVICE_HPP__
#define __BORC_MODEL_BUILDSERVICE_HPP__

#include "Compiler.hpp"
#include "Linker.hpp"

#include <filesystem>
#include <vector>

namespace borc::model {
	class BuildService {
	private:
		const Compiler *compiler;
		const Linker *linker;

		//! list of extension wildcards that will trigger a source file compilation with the current compiler
		const std::vector<std::string> compilerWildcards = {
			"*.c", "*.cpp", "*.c++", "*.cc", "*.cxx",
		};

	public:
		explicit BuildService(const Compiler *compiler, const Linker *linker) {
			this->compiler = compiler;
			this->linker = linker;
		}

		void buildProject(const Project *project) {
			auto modules = project->getModules();

			int builtModules = 0;

			for (const Module *module : modules) {
				std::cout << "Building module " << module->getName() << " ..." << std::endl;

				const auto files = module->getFiles();

				std::vector<std::string> objectFiles;
				std::copy_if(files.begin(), files.end(), std::back_inserter(objectFiles), [&](const auto &file) {
					return this->isFileCompilable(file);
				});

				std::transform(objectFiles.begin(), objectFiles.end(), objectFiles.begin(), [&](const auto &file) {
					return this->compiler->compile(project, module, file);
				});

				linker->link(project, module, objectFiles);

				builtModules++;
			}

			std::cout << "Built " << builtModules << " module(s)." << std::endl;
		}

	private:
		bool isFileCompilable(const std::string &file) const {
			const std::string ext = "*" + std::filesystem::path(file).extension().string();

			auto it = std::find(compilerWildcards.begin(), compilerWildcards.end(), ext);

			return it != compilerWildcards.end();
		}
	};
}


#endif
