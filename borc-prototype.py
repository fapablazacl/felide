"""
BORC Build System CLI Prototype Scripts.
For now, acts like a CMake Frontend
"""

import sys
import os
import subprocess

class GCCConfiguration:
    def __init__(self, specs):
        self.key = "gcc"
        self.name = "GNU Compiler Collection"
        self.target = self.__parseProperty(specs[3])
        self.threadModel = self.__parseProperty(specs[5])
        self.version = self.__parseVersion(specs[6])

    def __parseProperty(self, rawTarget):
        return rawTarget[rawTarget.find(":") + 1:].strip()
        
    def __parseVersion(self, rawVersion):
        return rawVersion.split(" ")[2]


class ProjectConfiguration:
    def __init__(self, compiler):
        self.__compiler = compiler
        self.__baseBuildPath = 

    def getBuildDirectory(self, buildConfiguration):
        pass


class Borc:
    def __init__(self):
        pass
    
    def setup(self):
        os.makedirs(".borc", exist_ok=True)

        # detect compiler information
        print("Detecting compiler ...")
        process = subprocess.Popen(["gcc", "-v"], stderr=subprocess.PIPE)
        specs = process.stderr.read().decode("utf-8").split("\n")
        config = GCCConfiguration(specs)

        compilerKey = config.key
        compilerName = config.name
        compilerVersion = config.version
        compilerTarget = config.target

        # generate CMake build scripts ...
        print(f"Using the '{compilerName}' toolchain, version {compilerVersion}")
        print("Bootstraping CMake build scripts ...")
        os.makedirs(f".borc/{compilerKey}({compilerTarget})/{compilerVersion}", exist_ok=True)

        buildConfigs = ["Debug", "Release"]

        for buildConfig in buildConfigs:
            print (f"    -> Generating {buildConfig} build configuration")

            buildDir = f".borc/{compilerKey}({compilerTarget})/{compilerVersion}/{buildConfig}"
            os.makedirs(buildDir, exist_ok=True)

            process = subprocess.Popen(
                ["cmake", "../../../../", f"-DCMAKE_BUILD_TYPE={buildConfig}"], 
                cwd=buildDir, 
                stdout=subprocess.PIPE, 
                stderr=subprocess.PIPE
            )

            if process.wait() != 0:
                print (f"    Error while generating build configuration:")
                print(process.stderr.read().decode("utf-8"))

                return
        
        print ("Build scripts generation was successful.")

    def build(self):
        print ("Triggering CMake Build ...")

    def run(self):
        print ("Usage: borc run target")
    
    def showHelp(self):
        print ("Syntax:")
        print ("    borc subcommand --options")
        print ("")
        print ("Available subcommands:")
        print ("    build: Builds all the modules for the current project")
        print ("    setup: Setup a specific toolchain for use in the current project")
        print ("    run: Run an executable, optionally debugging it")
        print ("")
        print ("For specific use for a subcommand, use the --help switch, like:")
        print ("    borc setup --help")


class BorcDriver:
    def __init__(self, borc):
        self.__borc = borc

    def drive(self, argv):
        if len(sys.argv) < 2:
            print ("Borc Build System 0.0")
            print ("Error: No options specified. Use borc --help for help.")

            return

        subcommand = sys.argv[1]

        if subcommand == "setup":
            self.__borc.setup()

        if subcommand == "build":
            self.__borc.build()

        if subcommand == "run":
            self.__borc.run()

        if subcommand == "--help":
            self.__borc.showHelp()

borc = Borc()
driver = BorcDriver(borc)
driver.drive(sys.argv)
