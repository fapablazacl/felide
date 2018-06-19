
#include <catch.hpp>

#include <Felide/POM/Source.hpp>
#include <Felide/FileType.hpp>
#include <Felide/FileTypeRegistry.hpp>

TEST_CASE("FileTypeRegistryImpl Test Case", "Felide::FileTypeRegistryImpl") {
    Felide::FileType fileType{"Java Files", {".java", ".class"}};
    Felide::FileType fileType2{"C++ Source Files", {".cpp", ".cc", ".cxx", ".c++"}};

    SECTION("addFileType method should") {
        SECTION("append the C++ File Type correctly") {
            auto registry = Felide::FileTypeRegistry::create();
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
            auto registry = Felide::FileTypeRegistry::create();
            auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

            REQUIRE(javaFileType != nullptr);
            REQUIRE(javaFileType->name == "Java Files");
            REQUIRE(javaFileType->extensions.size() == 2);
            REQUIRE(javaFileType->extensions[0] == ".java");
            REQUIRE(javaFileType->extensions[1] == ".class");
        }

        SECTION("return a nullptr Felide::FielType when inserting an empty extension list") {
            auto registry = Felide::FileTypeRegistry::create();
            
            auto csFileType = registry->addFileType("CS Files", {});

            REQUIRE(csFileType == nullptr);
        }

        SECTION("return a different file type instance for each invocation") {
            auto registry = Felide::FileTypeRegistry::create();

            auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});
            auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

            REQUIRE(cppFileType != javaFileType);
        }
    }

    SECTION("getFileType method should detect file types correctly") {
        auto registry = Felide::FileTypeRegistry::create();

        auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});
        auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

        Felide::Source cppSource("main.cc", nullptr);
        Felide::Source javaClass("main.class", nullptr);
        Felide::Source csClass("Main.cs", nullptr);

        REQUIRE(registry->getFileType(&cppSource) == cppFileType);
        REQUIRE(registry->getFileType(&javaClass) == javaFileType);
        REQUIRE(registry->getFileType(&csClass) == nullptr);
    }
}
