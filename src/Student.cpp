#include "Student.hpp"

Student::Student()
{
    InitializeNumClasses();
}

Student::Student(const std::string& newName, const std::string& newRoll)
        : name(newName), roll(newRoll)
{
    InitializeNumClasses();
}

const std::string& Student::GetName() const
{
    return name;
}

void Student::SetName(const std::string& newName)
{
    name = newName;
}

const std::string& Student::GetRoll() const
{
    return roll;
}

void Student::SetRoll(const std::string& newRoll)
{
    roll = newRoll;
}

unsigned Student::GetAttendedClasses() const
{
    return numClassesAttended;
}

void Student::AttendClass()
{
    numClassesAttended++;
}

void Student::SetAttendedClasses(unsigned newAttendedClasses)
{
    numClassesAttended = newAttendedClasses;
}

void Student::InitializeNumClasses()
{
    numClassesAttended = 0;
}

bool Student::operator==(const Student& other) const
{
    return roll == other.GetRoll() &&
           name == other.GetName() &&
           numClassesAttended == other.GetAttendedClasses();
}


std::ostream& operator<<(std::ostream& out, const Student& student)
{
    out << student.GetName() << "\n";
    out << student.GetRoll() << "\n";
    out << student.GetAttendedClasses() << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Student& student)
{
    std::string name;
    std::string roll;
    std::string attendedClassesStr;

    std::getline(in, name);
    std::getline(in, roll);
    std::getline(in, attendedClassesStr);

    student = Student{name, roll};

    int attendedClassesInt = std::stoi(attendedClassesStr);
    if (attendedClassesInt < 0) {
        std::stringstream errorStream;
        errorStream << "Number of attended classes can't be negative. ";
        errorStream << "Given: " << attendedClassesInt;

        throw std::domain_error(errorStream.str());
    }

    auto attendedClasses = static_cast<unsigned> (attendedClassesInt);
    student.SetAttendedClasses(attendedClasses);

    return in;
}
