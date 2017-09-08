#include "catch.hpp"

#include "StudentContainer.hpp"

TEST_CASE("StudentContainers can be be used as a container", "[StudentContainer]") {
    StudentContainer sc;

    SECTION("Can construct StudentContainers") {
        REQUIRE(sc.GetSize() == 0);
    }

    SECTION("Can add things to a StudentContainer") {
        Student s1 {"Person Lastname", "Roll20"};
        Student s2 {"SecondPerson Lastname", "Roll21"};
        Student s3 {"ThirdPerson Lastname", "Roll22"};

        sc.AddStudent(s1);
        sc.AddStudent(s2);
        sc.AddStudent(s3);

        REQUIRE(sc.GetSize() == 3);
        REQUIRE(sc.GetStudentByIndex(0) == s1);
        REQUIRE(sc.GetStudentByIndex(1) == s2);
        REQUIRE(sc.GetStudentByIndex(2) == s3);
    }

    SECTION("Can remove things from a StudentContainer") {
        Student s1 {"Person Lastname", "Roll20"};
        Student s2 {"SecondPerson Lastname", "Roll21"};
        Student s3 {"ThirdPerson Lastname", "Roll22"};

        sc.AddStudent(s1);
        sc.AddStudent(s2);
        sc.AddStudent(s3);

        sc.RemoveStudent(s1);

        REQUIRE(sc.GetSize() == 2);
        REQUIRE(!(sc.GetStudentByIndex(0) == s1));
    }

    SECTION("StudentContainer throws exceptions when used erraneously.") {
        Student s1 {"Person Lastname", "Roll20"};
        Student s2 {"SecondPerson Lastname", "Roll21"};
        Student s3 {"ThirdPerson Lastname", "Roll22"};

        sc.AddStudent(s1);
        sc.AddStudent(s2);
        sc.AddStudent(s3);

        REQUIRE_THROWS(sc.GetStudentByIndex(3));
        REQUIRE_THROWS(sc.GetStudentByRoll("Roll24"));
    }
}

TEST_CASE("StudentContainer provides access via an iterator.") {
    Student s1 {"Person Lastname", "Roll20"};
    Student s2 {"SecondPerson Lastname", "Roll21"};
    Student s3 {"ThirdPerson Lastname", "Roll22"};

    StudentContainer sc;
    sc.AddStudent(s1);
    sc.AddStudent(s2);
    sc.AddStudent(s3);

    auto iter = sc.GetIterator();
    REQUIRE(iter.GetNext() == s1);
    REQUIRE(iter.GetNext() == s2);
    REQUIRE(iter.GetNext() == s3);
    REQUIRE(!iter.HasNext());
}

TEST_CASE("StudentContainers can be serialized and deserialized.") {
    Student s1 {"Person Lastname", "Roll20"};
    Student s2 {"SecondPerson Lastname", "Roll21"};
    Student s3 {"ThirdPerson Lastname", "Roll22"};

    StudentContainer sc;
    sc.AddStudent(s1);
    sc.AddStudent(s2);
    sc.AddStudent(s3);

    std::stringstream sstream;
    sstream << sc;

    StudentContainer sc2;
    sstream >> sc2;

    REQUIRE(sc == sc2);
}
