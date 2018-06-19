
#include <catch.hpp>
#include <borc/FileType.hpp>

TEST_CASE("FileType Test Case", "borc::FileType") {
    borc::FileType fileType{"Java Files", {".java", ".class"}};
    borc::FileType fileType2{"C++ Source Files", {".cpp", ".cc", ".cxx", ".c++"}};

    SECTION("constructor should set correctly the 'name' and 'extensions' attributes") {
        REQUIRE(fileType.name == "Java Files");
        REQUIRE(fileType.extensions.size() == 2);
        REQUIRE(fileType.extensions[0] == ".java");
        REQUIRE(fileType.extensions[1] == ".class");

        REQUIRE(fileType2.name == "C++ Source Files");
        REQUIRE(fileType2.extensions.size() == 4);
        REQUIRE(fileType2.extensions[0] == ".cpp");
        REQUIRE(fileType2.extensions[1] == ".cc");
        REQUIRE(fileType2.extensions[2] == ".cxx");
        REQUIRE(fileType2.extensions[3] == ".c++");
    }

    SECTION("check method should detect sources correctly") {
        REQUIRE(fileType.check(".java"));
        REQUIRE(fileType.check(".class"));
        REQUIRE(!fileType.check(".cpp"));
        REQUIRE(!fileType.check(".txt"));

        REQUIRE(!fileType2.check(".java"));
        REQUIRE(!fileType2.check(".class"));
        REQUIRE(fileType2.check(".cpp"));
        REQUIRE(fileType2.check(".cxx"));
        REQUIRE(fileType2.check(".cc"));
        REQUIRE(fileType2.check(".c++"));
        REQUIRE(!fileType2.check(".c"));
        REQUIRE(!fileType2.check(".txt"));
    }
}
