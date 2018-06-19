BORC
====

Introduction
------------

BORC pretends to accelerate the development of C/C++ applications offering some features not found in other build systems out there.


Planned Features
----------------

* Declarative, cross-platform, high-level orchestration description files.
* Work with more than one compiler simultaneosly (ideal for cross-compiling).
* Generates project stubs to start to work quickly.
* C++ library interface, for integration with other tools (mainly IDEs).
* Built-In support for git-based packages/repositories.
* Integration with other build systems.


C++ Planned Features
--------------------

* One build directory, automatic management for configurations, compilers, cpu architectures, etc
* Gives modularization of C/C++ projects via metadata in the description files.


Descriptable Entities
---------------------

* Software Artifacts (components, redistributables, manuals, etc), 
* Toolchains for not previously supported programming languages.
* File Types
* Actions
* Templates for various software artifacts, for a quickstart development.


BORC Definitions
-------------------------

A Project:
* Has a collection of Artifacts

A Artifact:
* Is based on a Archetype.
* Is defined by a collection of Files
* Supports a certain set of Actions

A Archetype:
* Is a Software Artifact Definition, used to "derive" concrete artifacts.
* Has a set of predefined Actions
* References a set of predefined Toolchains Kinds

A Toolchain:
* Is a collection of Compilers and Linkers.
* They are used to Build a artifact.

A Toolchain:
* Is a collection of Compilers and Linkers.
* They are used to Build a artifact.

A Action:
* Is an operation applied to a Artifact, that can use a given Toolchain or another entity.
* That operation needs:
  * A subset of the Files contained on a Artifact (¿Why a subset?)
  * A Toolchain in order to process those Files 
* That operation also can have Arguments.


BORC Command Line Utility
-------------------------

The BORC Command Line Utility is the main interface for "regular" users (developers using it for managing their build system needs).
This utility must be used in order to:

* Setup an initial development project.
* Configure it with several toolchains for different purposes and/or aspects.
* Update a project, giving more capabilities, purposes, or aspects during build-time.
* Perform the building of all the targets for a fiven development project.
* (pending to add another definitions)

Scenario 1: A simple console application, that outputs 'HelloWorld from Sample Project!'
----------------------------------------------------------------------------------------

$ borc --help
  BORC Build Orchestrator 0.0.0 (GIT commit aaaaaaaaaaaaaaaa)
  
$ borc
  Not a valid BORC directory (no file main.borc nor .borc directory)
  Use 'borc init' to setup an initial project

$ borc --working-directory sample-project/
  project SampleProject project, version 1.0.0
    artifact SampleProgram (cplusplus/executable)

$ cd sample-project

$ borc 
  (same output as before)

$ borc run 
  Error: there is no a default artifact. Please, select one with 
    borc --set-default-artifact artifactName
    
$ borc --set-default-artifact SampleProgram

$ borc run 
  Building artifact SampleProgram (Debug, x64)  ...
  Done.
  HelloWorld from Sample Project!

$ borc run
  HelloWorld from Sample Project!

$ borc artifact add SampleLibrary
  Added new artifact

Scenario 2: Multimedia engine project (XE)
-----------------------------------------------------------------------------
Let's suppose we have this C++ based project. It's a multimedia engine, used to make games in 3D, with bindings to Python and the Web and has the following structure:

Folder structure::
  xe/
    src/
      xe-core/
        xe/ ...
        xe-core.borc
      xe-gfx-gl3/
        xe/ ...
        xe-gfx-gl3.borc
      xe-gfx-es2/
        xe/ ...
        xe-gfx-es2.borc
      xe-sfx-al/
        xe/ ...
        xe-sfx-al.borc
      xe-python/
        xe/
        xe-python.borc
      xe-js/
        xe/
        xe-js.borc
    main.borc

Because we need to interact with another languages and systems, we require:
  * A C++ toolchain (arch: host)
  * A C++ toolchain (arch: WebAssembly, required for the Web port, optional)
  * A Python toolchain (arch: host, required for python bindings, optional)
  * A Android SDK and NDK (arch: host, artifact arch: ARM/x86, required for android bindings, optional).

As we can see, there is plenty of choices and configuration combinations.

In order to configure this project, let's run the following command::
  $ cd /path/to/project/xe
  $ borc configure

  Configuring project 'xe' ...
  Scanning targets, dependencies and requirements ...
  Cloning Git repositories ...

  Using default toolchains
    [C++] Emscripten Compiler, version 4.2.0, targeting WebAssembly, with static runtime library.
    [C++] GCC Compiler, version 7.1.0, targeting x64, with shared runtime library
    [Python] 
  
We need to compiler 
    .borc/
      {compiler}/
        {configuration}/
          {projectName}/
            bin/
              MyProject[.exe]
            obj/
              MyProject.cpp.obj
 