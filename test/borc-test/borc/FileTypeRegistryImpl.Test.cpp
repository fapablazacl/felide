
#include <catch.hpp>

#include <felide/pom/Source.hpp>
#include <felide/FileType.hpp>
#include <felide/FileTypeRegistry.hpp>

TEST_CASE("FileTypeRegistryImpl Test Case", "felide::FileTypeRegistryImpl") {
    felide::FileType fileType{"Java Files", {".java", ".class"}};
    felide::FileType fileType2{"C++ Source Files", {".cpp", ".cc", ".cxx", ".c++"}};

    SECTION("addFileType method should") {
        SECTION("append the C++ File Type correctly") {
            auto registry = felide::FileTypeRegistry::create();
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
            auto registry = felide::FileTypeRegistry::create();
            auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

            REQUIRE(javaFileType != nullptr);
            REQUIRE(javaFileType->name == "Java Files");
            REQUIRE(javaFileType->extensions.size() == 2);
            REQUIRE(javaFileType->extensions[0] == ".java");
            REQUIRE(javaFileType->extensions[1] == ".class");
        }

        SECTION("return a nullptr felide::FielType when inserting an empty extension list") {
            auto registry = felide::FileTypeRegistry::create();
            
            auto csFileType = registry->addFileType("CS Files", {});

            REQUIRE(csFileType == nullptr);
        }

        SECTION("return a different file type instance for each invocation") {
            auto registry = felide::FileTypeRegistry::create();

            auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});
            auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

            REQUIRE(cppFileType != javaFileType);
        }
    }

    SECTION("getFileType method should detect file types correctly") {
        auto registry = felide::FileTypeRegistry::create();

        auto cppFileType = registry->addFileType("C++ Source File", {".cpp", ".cc", ".cxx", ".c++"});
        auto javaFileType = registry->addFileType("Java Files", {".java", ".class"});

        felide::Source cppSource("main.cc", nullptr);
        felide::Source javaClass("main.class", nullptr);
        felide::Source csClass("Main.cs", nullptr);

        REQUIRE(registry->getFileType(&cppSource) == cppFileType);
        REQUIRE(registry->getFileType(&javaClass) == javaFileType);
        REQUIRE(registry->getFileType(&csClass) == nullptr);
    }
}
