#include "catch.hpp"

#include "Student.hpp"

TEST_CASE ("Students can be created.", "[Student]")
{
    SECTION("Empty students can be created") {
        Student s;

        REQUIRE (s.GetAttendedClasses() == 0);
        REQUIRE (s.GetName() == "");
        REQUIRE (s.GetRoll() == "");
    }

    SECTION("Students can be created via constant character arrays.") {
        Student s{"Person Lastname", "Roll20"};

        REQUIRE (s.GetName() == "Person Lastname");
        REQUIRE (s.GetRoll() == "Roll20");
    }

    SECTION("Students can be created via constant string references.") {
        const std::string studentName = "Person Lastname";
        const std::string& studentNameRef = studentName;

        const std::string studentRoll = "Roll20";
        const std::string& studentRollRef = studentRoll;

        Student s{studentNameRef, studentRollRef};
        REQUIRE (s.GetName() == "Person Lastname");
        REQUIRE (s.GetRoll() == "Roll20");
    }
}

TEST_CASE("Students can used as holding attendance records.", "[student]")
{
    Student s{"Person Lastname", "Roll20"};

    SECTION("Can retrieve information from students.") {
        REQUIRE (s.GetName() == "Person Lastname");
        REQUIRE (s.GetRoll() == "Roll20");
    }

    SECTION("Can change the name") {
        s.SetName("New Person");

        REQUIRE (s.GetName() == "New Person");
    }

    SECTION("Can change the roll") {
        s.SetRoll("42");
        REQUIRE (s.GetRoll() == "42");
    }

    SECTION("Students start out not having attended any classes.") {
        REQUIRE(s.GetAttendedClasses() == 0);
    }

    SECTION("Students can attend classes.") {
        s.AttendClass();
        REQUIRE(s.GetAttendedClasses() == 1);

        s.AttendClass();
        s.AttendClass();
        REQUIRE(s.GetAttendedClasses() == 3);
    }

    SECTION("Students can have their attendance manually set") {
        s.SetAttendedClasses(10);
        REQUIRE(s.GetAttendedClasses() == 10);
    }
}

TEST_CASE("Students can be serialized via streams", "[Student]")
{
    SECTION("Students can be serialized out to streams") {
        Student s{"Person Lastname", "Roll20"};
        s.SetAttendedClasses(10);

        std::stringstream stream;
        stream << s;

        REQUIRE(stream.str() == "Person Lastname\nRoll20\n10\n");
    }

    SECTION("Students can be deserialized via streams") {
        Student s;

        std::stringstream stream;
        stream << "Person Lastname\nRoll20\n10\n";
        stream >> s;

        REQUIRE(s.GetName() == "Person Lastname");
        REQUIRE(s.GetRoll() == "Roll20");
        REQUIRE(s.GetAttendedClasses() == 10);
    }

    SECTION("Students cannot be deserialized when they have negative attendance") {
        Student s;

        std::stringstream stream;
        stream << "Person Lastname\nRoll20\n-10\n";
        REQUIRE_THROWS(stream >> s);
    }
}
