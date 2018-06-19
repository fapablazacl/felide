
#include <borc/Version.hpp>
#include <ostream>

namespace borc {
    std::ostream& operator<< (std::ostream &os, const Version &version) {
        return os << version.toString();
    }
}

#include <catch.hpp>

TEST_CASE("Version Test Case", "borc::Version") {
    SECTION("constructor should set the parameters correctly") {
        auto version1 = borc::Version();
        REQUIRE(version1.getMajor() == 0);
        REQUIRE(version1.getMinor() == 0);
        REQUIRE(version1.getRevision() == 0);

        auto version2 = borc::Version(1);
        REQUIRE(version2.getMajor() == 1);
        REQUIRE(version2.getMinor() == 0);
        REQUIRE(version2.getRevision() == 0);

        auto version3 = borc::Version(1, 2);
        REQUIRE(version3.getMajor() == 1);
        REQUIRE(version3.getMinor() == 2);
        REQUIRE(version3.getRevision() == 0);

        auto version4 = borc::Version(1, 2, 3);
        REQUIRE(version4.getMajor() == 1);
        REQUIRE(version4.getMinor() == 2);
        REQUIRE(version4.getRevision() == 3);
    }

    SECTION("comparison operators should operate correctly") {
        REQUIRE(borc::Version(0, 0, 0) == borc::Version(0, 0, 0));
        REQUIRE(borc::Version(1, 0, 0) == borc::Version(1, 0, 0));
        REQUIRE(borc::Version(1, 2, 0) == borc::Version(1, 2, 0));
        REQUIRE(borc::Version(1, 2, 5) == borc::Version(1, 2, 5));
        REQUIRE(borc::Version(1, 0, 0) != borc::Version(0, 0, 0));
        REQUIRE(borc::Version(0, 0, 0) != borc::Version(1, 0, 0));

        REQUIRE(borc::Version(0, 0, 0) >= borc::Version(0, 0, 0));
        REQUIRE(borc::Version(1, 0, 0) >= borc::Version(1, 0, 0));
        REQUIRE(borc::Version(1, 2, 0) >= borc::Version(1, 2, 0));

        REQUIRE(borc::Version(0, 0, 0) <= borc::Version(0, 0, 0));
        REQUIRE(borc::Version(1, 0, 0) <= borc::Version(1, 0, 0));
        REQUIRE(borc::Version(1, 2, 0) <= borc::Version(1, 2, 0));

        REQUIRE(borc::Version(0, 0, 0) < borc::Version(1, 0, 0));
        REQUIRE(borc::Version(0, 0, 0) < borc::Version(0, 1, 0));
        REQUIRE(borc::Version(0, 0, 0) < borc::Version(0, 0, 1));

        REQUIRE(borc::Version(1, 0, 0) > borc::Version(0, 0, 0));
        REQUIRE(borc::Version(0, 1, 0) > borc::Version(0, 0, 0));
        REQUIRE(borc::Version(0, 0, 1) > borc::Version(0, 0, 0));
    }

    SECTION("setters should behave correctly") {
        auto version = borc::Version();
        
        REQUIRE(version.setMajor(1) == version);
        REQUIRE(version.getMajor() == 1);

        REQUIRE(version.setMinor(2) == version);
        REQUIRE(version.getMinor() == 2);

        REQUIRE(version.setRevision(1000) == version);
        REQUIRE(version.getRevision() == 1000);

        SECTION("and should throw exceptions when passing negative version numbers") {
            REQUIRE_THROWS(version.setMajor(-1));
            REQUIRE_THROWS(version.setMinor(-2));
            REQUIRE_THROWS(version.setRevision(-3));
        }
    }

    SECTION("setters and getters should behave correctly") {
        auto version = borc::Version();
        
        REQUIRE(version.setMajor(1) == version);
        REQUIRE(version.getMajor() == 1);

        REQUIRE(version.setMinor(2) == version);
        REQUIRE(version.getMinor() == 2);

        REQUIRE(version.setRevision(1000) == version);
        REQUIRE(version.getRevision() == 1000);
    }

    SECTION("toString method should format the output correctly") {
        auto version1 = borc::Version();
        REQUIRE(version1.toString() == "0.0.0");

        auto version2 = borc::Version(1, 2, 3);
        REQUIRE(version2.toString() == "1.2.3");
    }

    SECTION("compare method should return only one of three responses") {
        REQUIRE(borc::Version(1, 2, 3).compare(borc::Version(1, 2, 1)) == borc::VersionComparisonResult::Greater);
        REQUIRE(borc::Version(1, 2, 3).compare(borc::Version(1, 3, 1)) == borc::VersionComparisonResult::Lesser);
        REQUIRE(borc::Version(1, 2, 3).compare(borc::Version(1, 2, 3)) == borc::VersionComparisonResult::Equal);
    }
}
