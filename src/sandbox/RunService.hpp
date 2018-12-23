
#ifndef __BORC_MODEL_RUNSERVICE_HPP__
#define __BORC_MODEL_RUNSERVICE_HPP__

//! Project Model for C/C++
namespace borc::model {
	class Compiler;
	class Linker;
	class Module;

	class RunService {
	public:
		explicit RunService(const Compiler *compiler, const Linker *linker);

		void runModule(const Module *module);

	private:
		const Compiler *compiler;
		const Linker *linker;
	};
}

#endif
