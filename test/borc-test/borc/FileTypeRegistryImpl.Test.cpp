
#include <catch.hpp>

#include <borc/pom/Source.hpp>
#include <borc/FileType.hpp>
#include <borc/FileTypeRegistry.hpp>

TEST_CASE("FileTypeRegistryImpl Test Case", "borc::FileTypeRegistryImpl") {
    borc::FileType fileType{"Java Files", {".java", ".class"}};
    borc::FileType fileType2{"C++ Source Files", {".cpp", ".cc", ".cxx", ".c++"}};

    SECTION("addFileType method should") {
        SECTION("append the C++ File Type correctly") {
            auto registry = borc::FileTypeRegistry::create();
            auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});

            REQUIRE(cppFileType != nullptr);
            REQUIRE(cppFileType->name == "C++ Source File");
            REQUIRE(cppFileType->extensions.size() == 4);
            REQUIRE(cppFileType->extensions[0] == ".cpp");
            REQUIRE(cppFileType->extensions[1] == ".cc");
            REQUIRE(cppFileType->extensions[2] == ".cxx");
            REQUIRE(cppFileType->extensions[3] == ".c++");
        }

        SECTION("append the Java File Type correctly") {
            auto registry = borc::FileTypeRegistry::create();
            auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

            REQUIRE(javaFileType != nullptr);
            REQUIRE(javaFileType->name == "Java Files");
            REQUIRE(javaFileType->extensions.size() == 2);
            REQUIRE(javaFileType->extensions[0] == ".java");
            REQUIRE(javaFileType->extensions[1] == ".class");
        }

        SECTION("return a nullptr borc::FielType when inserting an empty extension list") {
            auto registry = borc::FileTypeRegistry::create();
            
            auto csFileType = registry->addFileType("CS Files", {});

            REQUIRE(csFileType == nullptr);
        }

        SECTION("return a different file type instance for each invocation") {
            auto registry = borc::FileTypeRegistry::create();

            auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});
            auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

            REQUIRE(cppFileType != javaFileType);
        }
    }

    SECTION("getFileType method should detect file types correctly") {
        auto registry = borc::FileTypeRegistry::create();

        auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});
        auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

        borc::Source cppSource("main.cc", nullptr);
        borc::Source javaClass("main.class", nullptr);
        borc::Source csClass("Main.cs", nullptr);

        REQUIRE(registry->getFileType(&cppSource) == cppFileType);
        REQUIRE(registry->getFileType(&javaClass) == javaFileType);
        REQUIRE(registry->getFileType(&csClass) == nullptr);
    }
}
